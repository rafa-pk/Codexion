*This project has been created as part of the 42 curriculum by rvaz-da-*

---

# Codexion

## Description
This project is an introduction to multi-threaded programming and concurrency. The goal is to implement a simulation very similar to that of the dining philosopher's problem, which is the following:
A group of coders is sitting around a quantum compiler with a USB-dongle between each one of them. They alternatively compile, debug and refactor. When doing one, they are not doing the other. In order to compile, they need to use both dongles left and right of them, and when they are finished compiling, they shall put them back on the table. The simulation stops either because they've compiled the expected amount of times or because a coder burned-out from a lack of compiling.
In the simulation, each coder is represented as a thread and each dongle as a mutex. The goal is to make the simulation run smoothly while avoiding deadlocks.

### Instructions
The project's executable is created via make, and arguments are then passed when running it.
**Available make rules:**

```
make                # compile code and create executable

make clean          # remove object files from working directory

make fclean         # remove object files and executable from working directory
```

Once make has been run, you can run the program as follows:

```
./codexion number_of_coders time_to_burnout time_to_compile time_to_debug time_to_refactor number_of_compiles_required dongle_cooldown scheduler
```

Where arguments have to comply to the following:
- number_of_coders: number of coders in simulation.
- time_to_burnout (in milisseconds): If coder hasn't started compiling within this timeframe since last compilation, it burns out.
- time_to_compile (in milisseconds): Time it takes coder to compile and for which it must have two dongles.
- time_to_debug (in milisseconds): Time it takes coder to debug.
- time_to_refactor (in milisseconds): Time it takes coder to refactor.
- number_of_compiles_required: If every coder has compiled successfully this amount of times, the simulation stops.
- dongle_cooldown (in milisseconds): The time a dongle is unavailable for after being released.
- scheduler (fifo/edf): The scheduler to be used to decide who gets the dongles first.
