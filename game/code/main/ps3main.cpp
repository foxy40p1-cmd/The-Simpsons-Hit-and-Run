//=============================================================================
// Copyright (C) 2002 Radical Entertainment Ltd.  All rights reserved.
//
// File:        ps3main.cpp
//
// Description: This file contains the main entry point to the game for PS3.
//
//=============================================================================

//========================================
// System Includes
//========================================
#include <string.h>
#include <stdlib.h>

// Foundation Tech
#include <raddebug.hpp>
#include <radobject.hpp>
#include <radthread.hpp>

//========================================
// Project Includes
//========================================
#include <main/game.h>
#include <main/ps3platform.h>
#include <main/singletons.h>
#include <main/commandlineoptions.h>
#include <memory/srrmemory.h>

//========================================
// Forward Declarations
//========================================
static void ProcessCommandLineArguments( int argc, char* argv[] );
static void ProcessCommandLineArgumentsFromFile( );

//=============================================================================
// Function:    main
//=============================================================================
int main( int argc, char* argv[] )
{
    //
    // All settings get stored in GameDB.
    //
    CommandLineOptions::InitDefaults();
    ProcessCommandLineArguments( argc, argv );

    //
    // Have to get FTech setup first so that we can use all the memory services.
    //
    PS3Platform::InitializeFoundation();

    srand (Game::GetRandomSeed ());

#ifndef RAD_RELEASE
    tName::SetAllocator (GMA_DEBUG);
#endif

    HeapMgr()->PushHeap (GMA_PERSISTENT);

	//Process any commandline options from the command.txt file
	ProcessCommandLineArgumentsFromFile();

    //
    // Instantiate all the singletons before doing anything else.
    //
    CreateSingletons();

    //
    // Construct the platform object.
    //
    PS3Platform* pPlatform = PS3Platform::CreateInstance();
    rAssert( pPlatform != NULL );

    //
    // Create the game object.
    //
    Game* pGame = Game::CreateInstance( pPlatform );
    rAssert( pGame != NULL );
    
    //
    // Initialize the game.
    //
    pGame->Initialize();

    HeapMgr()->PopHeap (GMA_PERSISTENT);

    //
    // Run it!  Control will not return from here until the game is stopped.
    //
    pGame->Run();
    
    //
    // Terminate the game (this frees all resources allocated by the game).
    //
    pGame->Terminate();
    
    //
    // Destroy the game object.
    //
    Game::DestroyInstance();
    
    //
    // Destroy the game and platform (do it in this order in case the game's 
    // destructor references the platform.
    //
    PS3Platform::DestroyInstance();
    
    //
    // Show some debug output
    //
#ifdef RAD_DEBUG
    radObject::DumpObjects();
#endif

    //
    // Dump all the singletons.
    //
    DestroySingletons();
    
    //
    // Pass any error codes back to the operating system.
    //
    return( 0 );
}


//=============================================================================
// Function:    ProcessCommandLineArguments
//=============================================================================
void ProcessCommandLineArguments( int argc, char* argv[] )
{
    rDebugPrintf( "*************************************************************\n" );
    rDebugPrintf( "Command Line Args:\n" );

    int i;
    for( i = 0; i < argc; ++i )
    {
        char* argument = argv[i];
        rDebugPrintf( "arg%d: %s\n", i, argument );
        CommandLineOptions::HandleOption( argument );
    }

    rDebugPrintf( "*************************************************************\n" );
}

void ProcessCommandLineArgumentsFromFile()
{
#ifndef FINAL
    IRadFile* pfile =NULL;
    
    ::radFileOpenSync(&pfile,"command.txt");

    if (pfile != NULL)
    {
        char commandlinestring [256];
        commandlinestring[ 0 ] = '\0';

        pfile->ReadSync(commandlinestring,255);

        char* argument = strtok(commandlinestring," ");
        while (argument != NULL)
        {
            CommandLineOptions::HandleOption(argument);
            argument=strtok(NULL," ");
        }
		pfile->Release();
    }
#endif //FINAL
}
