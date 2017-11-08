
set (PINEDIT_AUDIO_FILES bumphard.wav
bumpsoft.wav
bump.wav
flip.wav
gameover.wav
lock.wav
loop.wav
nudge.wav
opentux.wav
shoot.wav
up.wav)

install(FILES ${PINEDIT_AUDIO_FILES} DESTINATION share/games/${PINEDIT_EXEC_NAME}/audio)
