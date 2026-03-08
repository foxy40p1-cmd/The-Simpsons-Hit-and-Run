# CELL_GPU_TYPE (currently RSX is only one option)  
CELL_GPU_TYPE = RSX    
#CELL_PSGL_VERSION is debug, dpm or opt  
CELL_PSGL_VERSION = opt  

CELL_SDK ?= /usr/local/cell
CELL_MK_DIR ?= $(CELL_SDK)/samples/mk
include $(CELL_MK_DIR)/sdk.makedef.mk

CONTENT_ID = IV0002-PCSX00001_00-SAMPLE0000000001
MKFSELF_NPDRM = $(CELL_SDK)/host-win32/bin/make_fself_npdrm
MKPKG_NPDRM = $(CELL_SDK)/host-win32/bin/make_package_npdrm
MAKE_EBOOT = scetool --sce-type=SELF --compress-data=TRUE --skip-sections=FALSE --key-revision=04 --self-ctrl-flags=4000000000000000000000000000000000000000000000000000000000000002 --self-auth-id=1010000001000003 --self-app-version=0001000000000000 --self-add-shdrs=TRUE --self-vendor-id=01000002 --self-type=NPDRM --self-fw-version=0003004000000000 --np-license-type=FREE --np-content-id=$(CONTENT_ID) --np-app-type=EXEC --np-real-fname=EBOOT.BIN --encrypt 

PPU_OPTIMIZE_LV = -O2

ROOT_DIR = ../..
CODE_DIR = $(ROOT_DIR)/code

PPU_SRCS := \
	$(CODE_DIR)/ai/allai.cpp \
	$(CODE_DIR)/ai/actor/allactor.cpp \
	$(CODE_DIR)/ai/sequencer/allsequencer.cpp \
	$(CODE_DIR)/ai/vehicle/allaivehicle.cpp \
	$(CODE_DIR)/atc/allatc.cpp \
	$(CODE_DIR)/camera/allcamera.cpp \
	$(CODE_DIR)/cards/allcards.cpp \
	$(CODE_DIR)/cheats/allcheats.cpp \
	$(CODE_DIR)/console/allconsole.cpp \
	$(CODE_DIR)/contexts/allcontexts.cpp \
	$(CODE_DIR)/contexts/gameplay/allgameplay.cpp \
	$(CODE_DIR)/contexts/demo/alldemo.cpp \
	$(CODE_DIR)/data/alldata.cpp \
	$(CODE_DIR)/data/memcard/allmemcard.cpp \
	$(CODE_DIR)/debug/alldebug.cpp \
	$(CODE_DIR)/events/allevents.cpp \
	$(CODE_DIR)/gameflow/allgameflow.cpp \
	$(CODE_DIR)/input/allinput.cpp \
	$(CODE_DIR)/interiors/allinteriors.cpp \
	$(CODE_DIR)/loading/allloadmanager.cpp \
	$(CODE_DIR)/main/allps3main.cpp \
	$(CODE_DIR)/ps3_compat/ps3_debug_stubs.cpp \
	$(CODE_DIR)/memory/allmemory.cpp \
	$(CODE_DIR)/meta/allmeta.cpp \
	$(CODE_DIR)/mission/allmission.cpp \
	$(CODE_DIR)/mission/safezone/allsafezone.cpp \
	$(CODE_DIR)/mission/charactersheet/allcharactersheet.cpp \
	$(CODE_DIR)/mission/rewards/allrewards.cpp \
	$(CODE_DIR)/mission/conditions/allconditions.cpp \
	$(CODE_DIR)/mission/objectives/allobjectives.cpp \
	$(CODE_DIR)/presentation/allpresentation.cpp \
	$(CODE_DIR)/mission/respawnmanager/allrespawnmanager.cpp \
	$(CODE_DIR)/presentation/fmvplayer/allfmvplayerps3.cpp \
	$(CODE_DIR)/presentation/gui/allgui.cpp \
	$(CODE_DIR)/presentation/gui/bootup/allbootup.cpp \
	$(CODE_DIR)/presentation/gui/backend/allbackend.cpp \
	$(CODE_DIR)/presentation/gui/frontend/allfrontend.cpp \
	$(CODE_DIR)/presentation/gui/minigame/allminigame.cpp \
	$(CODE_DIR)/presentation/gui/ingame/allingame.cpp \
	$(CODE_DIR)/presentation/gui/ingame/hudevents/allhudevents.cpp \
	$(CODE_DIR)/presentation/gui/utility/allutility.cpp \
	$(CODE_DIR)/presentation/presevents/allpresevents.cpp \
	$(CODE_DIR)/render/Culling/allculling.cpp \
	$(CODE_DIR)/render/DSG/alldsg.cpp \
	$(CODE_DIR)/render/breakables/allbreakables.cpp \
	$(CODE_DIR)/worldsim/skidmarks/allskidmarks.cpp \
	$(CODE_DIR)/render/IntersectManager/allintersect.cpp \
	$(CODE_DIR)/render/Loaders/allloaders.cpp \
	$(CODE_DIR)/render/Particles/allparticles.cpp \
	$(CODE_DIR)/render/animentitydsgmanager/allanimentitydsgmanager.cpp \
	$(CODE_DIR)/render/RenderFlow/allrenderflow.cpp \
	$(CODE_DIR)/render/RenderManager/allrendermanager.cpp \
	$(CODE_DIR)/roads/allroads.cpp \
	$(CODE_DIR)/sound/allsound.cpp \
	$(CODE_DIR)/sound/avatar/allsoundavatar.cpp \
	$(CODE_DIR)/sound/dialog/alldialog.cpp \
	$(CODE_DIR)/sound/music/allmusic.cpp \
	$(CODE_DIR)/sound/nis/allnissound.cpp \
	$(CODE_DIR)/sound/soundfx/allsoundfx.cpp \
	$(CODE_DIR)/sound/soundrenderer/allsoundrenderer.cpp \
	$(CODE_DIR)/sound/tuning/allsoundtuning.cpp \
	$(CODE_DIR)/sound/sounddebug/allsounddebug.cpp \
	$(CODE_DIR)/sound/movingpositional/allmovingposn.cpp \
	$(CODE_DIR)/worldsim/allworldsim.cpp \
	$(CODE_DIR)/worldsim/coins/allcoins.cpp \
	$(CODE_DIR)/worldsim/character/allcharacter.cpp \
	$(CODE_DIR)/worldsim/redbrick/allredbrick.cpp \
	$(CODE_DIR)/worldsim/redbrick/vehiclecontroller/allvehiclecontroller.cpp \
	$(CODE_DIR)/worldsim/traffic/alltraffic.cpp \
	$(CODE_DIR)/pedpaths/allpedpaths.cpp \
	$(CODE_DIR)/worldsim/ped/allped.cpp \
	$(CODE_DIR)/worldsim/spawn/allspawn.cpp \
	$(CODE_DIR)/worldsim/harass/allharass.cpp \
	$(CODE_DIR)/stateprop/allstateprop.cpp \
	$(CODE_DIR)/mission/ufo/allufo.cpp \
	$(CODE_DIR)/worldsim/parkedcars/allparkedcars.cpp \
	$(CODE_DIR)/contexts/supersprint/allsupersprintctx.cpp \
	$(CODE_DIR)/supersprint/allsupersprint.cpp \
	$(CODE_DIR)/worldsim/character/footprint/allfootprint.cpp

PPU_TARGET		=	srr2.elf

PPU_CPPFLAGS	+= -D__BIGENDIAN__ -D__ppc__ -D_BIG_ENDIAN -DBIG_ENDIAN -D'PACKAGE_VERSION="1.0"' -DRAD_PS3 -DRAD_CONSOLE -DRAD_DEBUG -DPSGL -D_isnan=__builtin_isnan -DRAD_BIGENDIAN -D__PPC__ -D__big_endian__ -D__POWERPC__ -DPPC -DRAD_GAMECUBE

# Library and Include paths
LIBS_DIR = $(ROOT_DIR)/libs

PPU_CXXFLAGS	+=	-fno-strict-aliasing -I$(CODE_DIR) \
					-I$(CODE_DIR)/ps3_compat \
					-I$(CODE_DIR)/ps3_compat/strings \
					-I$(CODE_DIR)/ps3_compat/dolphin \
					-I$(CODE_DIR)/ps3_compat/charPipeline \
					-I$(LIBS_DIR)/radcore/inc \
					-I$(LIBS_DIR)/radmath \
					-I$(LIBS_DIR)/radcontent/inc \
					-I$(LIBS_DIR)/radscript/inc \
					-I$(LIBS_DIR)/radsound/inc \
					-I$(LIBS_DIR)/radmusic/inc \
					-I$(LIBS_DIR)/radmovie/inc \
					-I$(LIBS_DIR)/pure3d \
					-I$(LIBS_DIR)/sim \
					-I$(LIBS_DIR)/sim/inc \
					-I$(LIBS_DIR)/choreo \
					-I$(LIBS_DIR)/choreo/inc \
					-I$(LIBS_DIR)/poser/inc \
					-I$(LIBS_DIR)/scrooby/inc \
					-I$(LIBS_DIR)/sim/simcollision \
					-I$(LIBS_DIR)/sim/simphysics \
					-I$(LIBS_DIR)/radcore/inc/strings \
					-I$(LIBS_DIR)/scrooby/inc/strings

PPU_LDFLAGS		= -Wl -finline-limit=5000

# PS3 System Libraries
PPU_LIBS		+=	$(CELL_TARGET_PATH)/ppu/lib/libgcm_cmd.a \
					$(CELL_TARGET_PATH)/ppu/lib/libgcm_sys_stub.a $(CELL_TARGET_PATH)/ppu/lib/libfs_stub.a

PPU_LDLIBS		+= 	-L$(CELL_SDK)/target/ppu/lib/PSGL/RSX/opt -lPSGL -lPSGLcgc -lcgc -lsysmodule_stub 
PPU_LDLIBS		+=  -lresc_stub -lm -ldbgfont -lsysutil_stub -lio_stub -laudio_stub -lpthread -lsysutil_game_stub -lnet_stub

include $(CELL_MK_DIR)/sdk.target.mk

pkg: $(PPU_TARGET)
	$(PPU_STRIP) -s $< -o $(PPU_TARGET).stripped
	$(MKFSELF_NPDRM) $(PPU_TARGET).stripped release/NPDRM_RELEASE/USRDIR/EBOOT.BIN 
	$(CELL_HOST_PATH)/bin/psn_package_npdrm$(EXE_SUFFIX) release/package.conf release/NPDRM_RELEASE
