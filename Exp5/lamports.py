class LamportClock:
    def __init__(self, process_id):
        self.process_id = process_id
        self.clock = 0
        self.timestamps = []

    def increment(self):
        self.clock += 1
        self.timestamps.append(self.clock)
        print(f"Process {self.process_id} - Internal Event: {self.clock}")

    def send_event(self):
        self.increment()
        print(f"Process {self.process_id} sends message with timestamp: {self.clock}")
        return self.clock

    def receive_event(self, sender_timestamp):
        self.clock = max(self.clock, sender_timestamp) + 1
        self.timestamps.append(self.clock)
        print(f"Process {self.process_id} receives message. Updated clock: {self.clock}")

    def get_timestamps(self):
        return self.timestamps


if __name__ == "__main__":
    # Initialize two processes with their Lamport clocks
    process_P1 = LamportClock(process_id=1)
    process_P2 = LamportClock(process_id=2)
    process_P3 = LamportClock(process_id=3)

    # Events
    process_P1.increment()                  # Internal event in process 1

    timestamp_P1 = process_P1.send_event()   # Process 1 sends a message with its timestamp to 2

    process_P2.receive_event(timestamp_P1)   # Process 2 receives the message from 1

    process_P2.increment()                  # Internal event in process 2

    timestamp_P2 = process_P2.send_event() # Process 2 sends a message with its timestamp to 3

    process_P3.receive_event(timestamp_P2)   # Process 3 receives the message from 2

    # Collect timestamps for each process
    timestamps_P1 = process_P1.get_timestamps()
    timestamps_P2 = process_P2.get_timestamps()
    timestamps_P3 = process_P3.get_timestamps()   
   

    # Print the matrix
    print("\nLamport Clock Matrix:")
    print("Process 1:", timestamps_P1)
    print("Process 2:", timestamps_P2)
    print("Process 3:", timestamps_P3)
