*This project has been created as part of the 42 curriculum by rvaz-da-*

---

# Codexion

## Description
This project is an introduction to multi-threaded programming and concurrency. The goal is to implement a simulation very similar to that of the dining philosopher's problem, which is the following:
A group of coders is sitting around a quantum compiler with a USB-dongle between each one of them. They alternatively compile, debug and refactor. When doing one, they are not doing the other. In order to compile, they need to use both dongles left and right of them, and when they are finished compiling, they shall put them back on the table. The simulation stops either because they've compiled the expected amount of times or because a coder burned-out from a lack of compiling.
In the simulation, each coder is represented as a thread and each dongle as a mutex. The goal is to make the simulation run smoothly while avoiding deadlocks and burnout.

### Instructions
The project's executable is created via make, and arguments are then passed when running it.
**Available make rules:**

```
make                # compile code and create executable

make clean          # remove object files from working directory

make fclean         # remove object files and executable from working directory

make re             # make fclean + make
```

Once make has been run, a binary called 'codexion' has been created. You can run it as follows:

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

Note:
In order for the simulation to run smoothly to the end, time_to_burnout has to be at least > 2 * time_to_compile + time_to_debug + time_to_refactor + jitter (hardware dependent, accumulated time between calls)

### Blocking cases handled:
**Deadlock prevention**

Deadlock happens when a two threads are stuck in a state of inactivity where they are both stuck waiting for a resource held by the other.
In order for it to happen, 4 conditions have to come together — the Coffman's conditions:
1. Mutual exclusion (resources can't be shared, only a thread holds them at a time)
2. Hold and wait (threads hold one resource while requesting another)
3. No preemption (resources cannot be forcibly taken from a thread)
4. Circular wait (a closed chain of threads all dependent on the next one's resources)

In order to break circular wait, a global acquisition order was imposed — every coder always takes the lower-id dongle first, and the highest next. This makes hold-and-wait dynamics impossible regardless of the number of coders.

**Starvation prevention**

Starvation happens when the OS scheduler perpetually denies CPU time/shared resources to a thread and it essentially goes forgotten, eventhough it is available.
In order to avoid this, two schedulling policies have been implemented in a per-dongle heap queue:
1. FIFO (first-in-first-out) - the first thread to have claimed the dongle is the first one to get it
2. EDF (earliest deadline first) - the thread closest to burning out is the first one to get it.
EDF's deadline is calculated as: deadline = last_compile_start + time_to_burnout

Eventhough the standard way to implement these schedulling policies is through a min-heap (binary-tree structured array), I came to the conclusion that a fixed 2 coder capacity array was enough and much simpler. 
That is because:
- There are as many dongles as coders
- Every coder needs two dongles to compile
- No coder ever requests more than 2 dongles per turn, so a dongle's heap never has more than 2 elements in it

This means I simply have a fixed size void array, with swap, push and pop operations in order to make it work like a min-heap.

**Cooldown handling**

After a dongle is released, it cannot be taken again until `dongle_cooldown` milliseconds have elapsed. This is enforced in the availability predicate checked before every acquisition.
Coders waiting on a dongle sleep on its condition variable with a timed deadline computed from `released_at + cooldown`, so they wake at exactly the right moment without busy-waiting.

**Precise burnout detection**

The monitor thread checks every coder's time since last compile against `time_to_burnout` every 500 microseconds.
The death clock is updated under the coder's own mutex at three points — initialisation, thread routinestart, and each compile — to ensure the monitor never sees a stale value from before the thread existed.
A burnout is reported exactly once and is always the last line printed by broadcasting the end of the simulation to all threads, including those sleeping on condition variables.

**Log serialization**

All output printed to stdout is protected by a simulation mutex, which is held for the duration of the 'printf' call. This is done inside a custom function called 'printx', which is also called in case of burnout, ensuring no line is printed afterwards.

### Thread synchronisation mechanism:

```

pthread_mutex_t;         # per dongle, coder and simulation

pthread_cond_t;          # per dongle

```

Each dongle has its own mutex and condition variable. In order to both protect its internal state (expressed through taken, released_at and the heap) and to enable other coders to sleep on the condition if the dongle is taken.
The dongle mutex allows non-adjacent coders to acquire their dongles in parallel, as coder 0 locking dongle 1 does not affect coder 3 locking dongle 3 or 4. The associated condition variable allows for signalling to be targeted:
if a dongle is taken and coders try to claim it, they will sleep on the conditions to take the dongle, when it is finally available, no other coders then the ones sleeping will be woken up.
A mutex per coder is also implemented, protecting its information (compile_start, compile_count), which are tracked concurrently by the monitoring thread throughout the simulation.
The simulation also holds a shared mutex which allows for serialized output.

```
pthread_cond_timedwait(&dongle->cond, &dongle->mutex, &deadline);        # coder sleeps on the condition until it is met or deadline elapsed (deadline = cooldown_ms from when the dongle was last released)

pthread_cond_broadcast(&dongle->cond);                                   # broadcasts dongle status change to all coders sleeping on its condition variable

```

On shutdown signal (stop_sim() function), every dongle's condition variable gets broadcasted in order to correctly stop the simulation:
- All coders wake up
- They all check 'active'
- They all exit


**Atomic variables - 'active' and 'ticket_booth'**

Atomic variables enable read/write calls to be made in a single continuous sequence, always calling memory. So instead of reading the content of a register first, storing it and writing to it as separate operations, it does it all at once.
This avoids data races, as no one else can write to that register during that operation. 

sim->active is an atomic bool, read through atomic_load(). This means every thread can read it lock free from inside a dongle's critical section. Without it, reading the flag would imply nesting the simulation mutex inside a dongle mutex.
sim->ticket_booth is an atomic int, which gets incremented via atomic_fetch_add(). This means every coder will get a strictly unique and serialized order of arrival and no possibility of duplicates.


## Resources

### Documentation:
- Posix manual of every pthread function
- Github repos
- [Threads, Mutexes and Concurrent Programming in C](https://www.codequoi.com/en/threads-mutexes-and-concurrent-programming-in-c/) - Article by Mia Combeau about how concurrent programming works and its underlying issues
- [CS110 Lecture 10: Threads and Mutexes](https://web.stanford.edu/class/archive/cs/cs110/cs110.1204/static/lectures/10-threads-and-mutexes.pdf) - Stanford Principles of computer science lecture
- [Dining Philosophers Problem](https://en.wikipedia.org/wiki/Dining_philosophers_problem) - General wikipedia page for the philosophers problem
- [Oceano's medium article](https://medium.com/@jalal92/the-dining-philosophers-7157cc05315) - Guide and explanation to the philosopher's project
- [Oceano's youtube video](https://www.google.com/url?sa=t&source=web&rct=j&opi=89978449&url=https://www.youtube.com/watch%3Fv%3DzOpzGHwJ3MU&ved=2ahUKEwiyvvu5_PeUAxVkaqQEHSn8Fr0QwqsBegQIHBAB&usg=AOvVaw1JGuCycjQcKB0UdiL9yX_d) - Explanation of the problem
- [Reddit](www.reddit.com) - General information
- [Stack Overflow](www.stackoverflow.com) - Search of answers to frequently asked questions

### AI Usage
Claude was used in this project as a direct search-engine for some specific questions, as well as to further understand concepts I read about by being able to conversate about them.
It was also used to double-check/review my code to ensure thoroughness and to provide multiple test-cases.
No claude-produced code is in this project, all code was written by me.
