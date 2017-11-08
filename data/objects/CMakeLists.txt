
set (PINEDIT_OBJECTS_FILES left_arm.pbl
right_arm.pbl
bumper.pbl
lock1.pbl
lock2.pbl
releaselock.pbl
floor.pbl
stopper.pbl)

install(FILES ${PINEDIT_OBJECTS_FILES} DESTINATION share/games/${PINEDIT_EXEC_NAME}/objects)
