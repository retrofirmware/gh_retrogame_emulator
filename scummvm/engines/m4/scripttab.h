/* This file has been autogenerated by the linker.
   Do not edit it or merge it with script.cpp!     */
#define FUNCTION(x) { &ScriptInterpreter::x, #x }
	static KernelFunctionEntry kernelFunctions[] = {
		/* 000 */
		FUNCTION(o1_handleStreamBreak),
		FUNCTION(o1_handlePlayBreak),
		FUNCTION(o1_dispatchTriggerOnSoundState),
		FUNCTION(o1_getRangedRandomValue),
		/* 004 */
		FUNCTION(o1_getTicks),
		FUNCTION(o1_preloadSound),
		FUNCTION(o1_unloadSound),
		FUNCTION(o1_stopSound),
		/* 008 */
		FUNCTION(o1_playSound),
		FUNCTION(o1_playLoopingSound),
		FUNCTION(o1_setSoundVolume),
		FUNCTION(o1_getSoundStatus),
		/* 012 */
		FUNCTION(o1_getSoundDuration),
		FUNCTION(o1_loadSeries),
		FUNCTION(o1_unloadSeries),
		FUNCTION(o1_showSeries),
		/* 016 */
		FUNCTION(o1_playSeries),
		FUNCTION(o1_setSeriesFrameRate),
		FUNCTION(o1_playBreakSeries),
		FUNCTION(o1_preloadBreakSeries),
		/* 020 */
		FUNCTION(o1_unloadBreakSeries),
		FUNCTION(o1_startBreakSeries),
		FUNCTION(o1_dispatchTrigger),
		FUNCTION(o1_terminateMachine),
		/* 024 */
		FUNCTION(o1_sendWoodScriptMessage),
		FUNCTION(o1_runConversation),
		FUNCTION(o1_runConversation),
		FUNCTION(o1_loadConversation),
		/* 028 */
		FUNCTION(o1_exportConversationValue),
		FUNCTION(o1_exportConversationPointer),
		FUNCTION(o1_runConversation),
		FUNCTION(o1_fadeInit),
		/* 032 */
		FUNCTION(o1_fadeSetStart),
		FUNCTION(o1_fadeToBlack),
		FUNCTION(o1_initPaletteCycle),
		FUNCTION(o1_stopPaletteCycle),
		/* 036 */
		FUNCTION(o1_setHotspot),
		FUNCTION(o1_hideWalker),
		FUNCTION(o1_showWalker),
		FUNCTION(o1_setWalkerLocation),
		/* 040 */
		FUNCTION(o1_setWalkerFacing),
		FUNCTION(o1_walk),
		FUNCTION(o1_overrideCrunchTime),
		FUNCTION(o1_addBlockingRect),
		/* 044 */
		FUNCTION(o1_triggerTimerProc),
		FUNCTION(o1_setPlayerCommandsAllowed),
		FUNCTION(o1_getPlayerCommandsAllowed),
		FUNCTION(o1_updatePlayerInfo),
		/* 048 */
		FUNCTION(o1_hasPlayerSaid),
		FUNCTION(o1_hasPlayerSaidAny),
		FUNCTION(o1_playerHotspotWalkOverride),
		FUNCTION(o1_setPlayerFacingAngle),
		/* 052 */
		FUNCTION(o1_disablePlayerFadeToBlack),
		FUNCTION(o1_enablePlayer),
		FUNCTION(o1_disablePlayer),
		FUNCTION(o1_freshenSentence),
		/* 056 */
		FUNCTION(o1_playerHasItem),
		FUNCTION(o1_playerGiveItem),
		FUNCTION(o1_moveObject),
		FUNCTION(o1_setStopSoundsBetweenRooms),
		/* 060 */
		FUNCTION(o1_backupPalette),
		FUNCTION(o1_unloadWilburWalker),
		FUNCTION(o1_globalTriggerProc),
		FUNCTION(o1_wilburSpeech),
		/* 064 */
		FUNCTION(o1_wilburParse),
		FUNCTION(o1_wilburSaid),
		FUNCTION(o1_wilburTalk),
		FUNCTION(o1_wilburFinishedTalking)
	};
#undef FUNCTION

#define VARIABLE(x) { x, #x }
	static KernelVariableEntry kernelVars[] = {
		/* 000 */
		VARIABLE(kGameLanguage),
		VARIABLE(kGameVersion),
		VARIABLE(kGameCurrentRoom),
		VARIABLE(kGameNewRoom),
		/* 004 */
		VARIABLE(kGamePreviousRoom),
		VARIABLE(kGameNewSection),
		VARIABLE(kKernelTrigger),
		VARIABLE(kKernelTriggerMode),
		/* 008 */
		VARIABLE(kKernelFirstFade),
		VARIABLE(kKernelSuppressFadeUp),
		VARIABLE(kKernelContinueHandlingTrigger),
		VARIABLE(kKernelUseDebugMonitor),
		/* 012 */
		VARIABLE(kPlayerPosX),
		VARIABLE(kPlayerPosY),
		VARIABLE(kPlayerFacing),
		VARIABLE(kPlayerScale),
		/* 016 */
		VARIABLE(kPlayerDepth),
		VARIABLE(kPlayerWalkX),
		VARIABLE(kPlayerWalkY),
		VARIABLE(kPlayerReadyToWalk),
		/* 020 */
		VARIABLE(kPlayerNeedToWalk),
		VARIABLE(kPlayerCommandReady),
		VARIABLE(kPlayerWalkerInThisScene),
		VARIABLE(kPlayerVerb),
		/* 024 */
		VARIABLE(kWalkerInitialized),
		VARIABLE(kCallDaemonEveryLoop),
		VARIABLE(kConvCurrentTalker),
		VARIABLE(kConvCurrentNode),
		/* 028 */
		VARIABLE(kConvCurrentEntry),
		VARIABLE(kConvSoundToPlay),
		VARIABLE(kInterfaceVisible)
	};
#undef VARIABLE

