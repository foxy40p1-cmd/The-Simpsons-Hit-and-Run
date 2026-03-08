//===========================================================================
// Copyright (C) 2002 Radical Entertainment Ltd.  All rights reserved.
//
// Component:   PS3Platform   
//
// Description: Abstracts the differences for setting up and shutting down
//              the different platforms.
//
//===========================================================================

//========================================
// System Includes
//========================================
// PS3
#include <sys/process.h>

// Standard Lib
#include <stdlib.h>
#include <string.h>

// Pure 3D
#include <p3d/anim/compositedrawable.hpp>
#include <p3d/anim/expression.hpp>
#include <p3d/anim/multicontroller.hpp>
#include <p3d/anim/polyskin.hpp>
#include <p3d/anim/sequencer.hpp>
#include <p3d/anim/skeleton.hpp>
#include <p3d/camera.hpp>
#include <p3d/gameattr.hpp>
#include <p3d/image.hpp>
#include <p3d/imagefont.hpp>
#include <p3d/light.hpp>
#include <p3d/locator.hpp>
#include <p3d/platform.hpp>
#include <p3d/scenegraph/scenegraph.hpp>
#include <p3d/sprite.hpp>
#include <p3d/utility.hpp>
#include <p3d/texture.hpp>
#include <p3d/file.hpp>
#include <p3d/shader.hpp>
#include <p3d/matrixstack.hpp>
#include <p3d/memory.hpp>
#include <p3d/bmp.hpp>
#include <p3d/png.hpp>
#include <p3d/targa.hpp>
#include <p3d/font.hpp>
#include <p3d/texturefont.hpp>
#include <p3d/unicode.hpp>
#include <pddi/pddiext.hpp>

// Pure 3D: Loader-specific
#include <render/Loaders/GeometryWrappedLoader.h>
#include <render/Loaders/StaticEntityLoader.h>
#include <render/Loaders/StaticPhysLoader.h>
#include <render/Loaders/TreeDSGLoader.h>
#include <render/Loaders/FenceLoader.h>
#include <render/Loaders/IntersectLoader.h>
#include <render/Loaders/AnimCollLoader.h>
#include <render/Loaders/AnimDSGLoader.h>
#include <render/Loaders/DynaPhysLoader.h>
#include <render/Loaders/InstStatPhysLoader.h>
#include <render/Loaders/InstStatEntityLoader.h>
#include <render/Loaders/WorldSphereLoader.h>
#include <render/Loaders/BillboardWrappedLoader.h>
#include <render/Loaders/instparticlesystemloader.h>
#include <render/Loaders/breakableobjectloader.h>
#include <render/Loaders/lensflareloader.h>
#include <render/Loaders/AnimDynaPhysLoader.h>
#include <p3d/shadow.hpp>
#include <p3d/anim/animatedobject.hpp>
#include <p3d/anim/vertexanimkey.hpp>
#include <p3d/effects/particleloader.hpp>
#include <p3d/effects/opticloader.hpp>

// Foundation Tech
#include <raddebug.hpp>
#include <radthread.hpp>
#include <radplatform.hpp>
#include <radtime.hpp>
#include <radmemorymonitor.hpp>
#include <raddebugcommunication.hpp>
#include <raddebugwatch.hpp>
#include <radfile.hpp>
#include <radmovie2.hpp>
#include <radload/radload.hpp>
#include <radtextdisplay.hpp>

// sim - for InstallSimLoaders
#include <simcommon/simutility.hpp>
// StateProps 
#include <stateprop/statepropdata.hpp>

// To turn off movies during an error.
#include <presentation/fmvplayer/fmvplayer.h>
#include <presentation/presentation.h>

//========================================
// Project Includes
//========================================
#include <input/inputmanager.h>
#include <main/ps3platform.h>
#include <main/game.h>
#include <main/commandlineoptions.h>
#include <memory/srrmemory.h>
#include <render/RenderManager/RenderManager.h>
#include <render/Loaders/AllWrappers.h>

#include <loading/locatorloader.h>
#include <loading/cameradataloader.h>
#include <loading/roadloader.h>
#include <loading/pathloader.h>
#include <loading/intersectionloader.h>
#include <loading/roaddatasegmentloader.h>
#include <atc/atcloader.h>

#include <debug/debuginfo.h>

#include <sound/soundmanager.h>

#include <presentation/presentation.h>
#include <presentation/gui/guitextbible.h>
#include <data/gamedatamanager.h>

#include <cheats/cheatinputsystem.h>

#include <mission/gameplaymanager.h>
#include <pddi/pddi.hpp>

#define PS3_SECTION "PS3_SECTION"

IRadCementLibrary* PS3Platform::s_MainCement = NULL;
PS3Platform* PS3Platform::spInstance = NULL;

//******************************************************************************
//
// Public Member Functions
//
//******************************************************************************

PS3Platform* PS3Platform::CreateInstance()
{
    rAssert( spInstance == NULL );
    spInstance = new(GMA_PERSISTENT) PS3Platform;
    rAssert( spInstance );
    return spInstance;
}

PS3Platform* PS3Platform::GetInstance()
{
    rAssert( spInstance != NULL );
    return spInstance;
}

void PS3Platform::DestroyInstance()
{
    rAssert( spInstance != NULL );
    delete( GMA_PERSISTENT, spInstance );
    spInstance = NULL;
}

void PS3Platform::InitializeFoundation() 
{
    PS3Platform::InitializeMemory();
    
    HeapMgr()->PrepareHeapsStartup ();
    HeapMgr()->PushHeap (GMA_PERSISTENT);

    radPlatformGameMediaType mediaType = GameMediaDVD;

    ::radPlatformInitialize( NULL, 
                             GMA_PERSISTENT );
    
    ::radTimeInitialize();

    ::radDbgComTargetInitialize( Deci,
                                 radDbgComDefaultPort, 
                                 NULL,                 
                                 GMA_DEBUG );
    
#ifdef DEBUGWATCH
    ::radDbgWatchInitialize( "SRR2",
                             16384 * 32, 
                             GMA_DEBUG );
#endif

    ::radFileInitialize( 50, 
                         32, 
                         GMA_PERSISTENT );

	::radLoadInitialize( );

    ::radSetDefaultDrive( "HOSTDRIVE:" );
    ::radDriveMount( 0, GMA_PERSISTENT );

    ::radMovieInitialize2( GMA_PERSISTENT );

    ::radMathInitialize();

    HeapMgr()->PopHeap (GMA_PERSISTENT);
}

void PS3Platform::InitializeMemory()
{
    if( gMemorySystemInitialized == true )
    {
        return;
    }

    gMemorySystemInitialized = true;
    ::radThreadInitialize();
    ::radMemoryInitialize();
}

void PS3Platform::InitializePlatform() 
{
    HeapMgr()->PushHeap (GMA_PERSISTENT);
    
    InitializePure3D();

    InitializeFoundationDrive();

    GetInputManager()->Init();

    HeapMgr()->PopHeap (GMA_PERSISTENT);
}

void PS3Platform::ShutdownPlatform()
{
    ShutdownPure3D();
    ShutdownFoundation();
}

void PS3Platform::ResetMachine()
{
    // PS3 reset machine logic
    sys_process_exit(0);
}

void PS3Platform::LaunchDashboard()
{
    sys_process_exit(0);
}

void PS3Platform::DisplaySplashScreen( SplashScreen screenID, 
                                       const char* overlayText, 
                                       float fontScale, 
                                       float textPosX, 
                                       float textPosY,
                                       tColour textColour,
                                       int fadeFrames )
{
    // Simplified splash screen for now
}

void PS3Platform::DisplaySplashScreen( const char* textureName,
                                       const char* overlayText, 
                                       float fontScale, 
                                       float textPosX, 
                                       float textPosY, 
                                       tColour textColour,
                                       int fadeFrames )
{
    // Simplified splash screen for now
}

void PS3Platform::InitializeFoundationDrive() 
{
    ::radDriveOpen( &mpIRadDrive, 
                    "HOSTDRIVE:",
                    NormalPriority, 
                    GMA_PERSISTENT );

    mpIRadDrive->RegisterErrorHandler( this, NULL );
    rAssert( mpIRadDrive != NULL );
}

void PS3Platform::ShutdownFoundation()
{
    if ( s_MainCement ) {
        s_MainCement->Release();
        s_MainCement = NULL;
    }

    mpIRadDrive->Release();
    mpIRadDrive = NULL;

    ::radDriveUnmount();
    ::radFileTerminate();
    ::radDbgWatchTerminate();
    ::radDbgComTargetTerminate();
    ::radTimeTerminate();
    ::radPlatformTerminate();
    ::radMemoryTerminate();
    ::radThreadTerminate();
    ::radMovieTerminate2( );
}

void PS3Platform::InitializePure3D() 
{
    mpPlatform = tPlatform::Create();
    rAssert( mpPlatform != NULL );

    tContextInitData init;
    init.xsize = 640;
    init.ysize = 480;
    init.pal = false;
    init.lockToVsync = false;

    mpContext = mpPlatform->CreateContext( &init );
    rAssert( mpContext != NULL );

    mpPlatform->SetActiveContext( mpContext );
    
    p3d::pddi->EnableZBuffer( true );

    tP3DFileHandler* p3d = new(GMA_PERSISTENT) tP3DFileHandler;
    p3d::context->GetLoadManager()->AddHandler(p3d, "p3d");
    p3d::context->GetLoadManager()->AddHandler(new(GMA_PERSISTENT) tPNGHandler, "png");

    p3d::context->GetLoadManager()->AddHandler(new(GMA_PERSISTENT) tBMPHandler, "p3d");
    p3d::context->GetLoadManager()->AddHandler(new(GMA_PERSISTENT) tPNGHandler, "p3d");
    p3d::context->GetLoadManager()->AddHandler(new(GMA_PERSISTENT) tTargaHandler, "p3d");

    // Porting of loaders from PS2Platform.cpp should go here, similar to the original.
    // ...

    p3d::context->SetClearColour(tColour(0,0,0));
}

void PS3Platform::ShutdownPure3D()
{
    p3d::inventory->RemoveAllElements();
    p3d::inventory->DeleteAllSections();

    if( mpContext != NULL )
    {
        mpPlatform->DestroyContext( mpContext );
        mpContext = NULL;
    }

    if( mpPlatform != NULL )
    {
        tPlatform::Destroy( mpPlatform );
        mpPlatform = NULL;
    }
}

void PS3Platform::SetProgressiveMode( bool progressiveScan )
{
    mProgressiveMode = progressiveScan;
}

bool PS3Platform::CheckForStartupButtons( void )
{
    return false;
}

void PS3Platform::OnControllerError(const char *msg)
{
}

bool PS3Platform::OnDriveError( radFileError error, const char* pDriveName, void* pUserData )
{
    return true;
}

PS3Platform::PS3Platform() :
    mpPlatform( NULL ),
    mpContext( NULL )
{
}

PS3Platform::~PS3Platform()
{
}
