# channels-in-c

A simple channel implementation in C with pthreads (inspired by Go)

## Usage

This library defines a simple channel that can be used for communication between pthreads. The channel is implemented using a circular buffer, a mutex for synchronization, and condition variables to signal when data is available or when there's space to send data.

`channel_init`:
This initializes the channel, setting the front, rear, and count of the buffer to 0. The mutex and the condition variables notEmpty and notFull are also initialized. These will be used to synchronize access to the buffer and to allow threads to wait when the channel is full or empty.

`channel_send`:
This is used by a producer to send a value to the channel.

The function first locks the mutex to ensure exclusive access to the channel.
It then waits on the notFull condition variable if the channel is full (i.e., count is equal to CHANNEL_SIZE).
Once there's space in the channel, it adds the value to the buffer at the rear position and updates rear and count.
Finally, it signals the notEmpty condition variable to wake up any waiting consumers, and then unlocks the mutex.

`channel_receive`:
This is used by a consumer to receive a value from the channel.

It locks the mutex and then waits on the notEmpty condition variable if the channel is empty.
Once there's an item in the channel, it retrieves the value from the buffer at the front position and updates front and count.
It then signals the notFull condition variable to wake up any waiting producers and unlocks the mutex.
The retrieved value is then returned.

`channel_destroy`:
This cleans up the channel, destroying the mutex and the condition variables. It should be called when the channel is no longer needed.

Overall, the code allows threads to send and receive values through the channel, with blocking behavior when the channel is full or empty, similar to Go channels. It's a useful pattern for synchronizing and communicating between threads in a multithreaded program.
