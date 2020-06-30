Memmory = 256 signed 8-bit cells
X = unsigned 8-bit register
Program counter starts at 0
256 program "instruction" slots

G = GRAB X, N            // Read X from mem[N]
O = OFFER X, N           // Write X to mem[N]
R = RECEIVE X            // Reads from input stream into X
B = BRANCH X == 0, N     // If X == 0, goto instruction N
I = INCREASE X, N        // Adds N to X register
T = TRANSMIT X           // Writes X to output stream
S = SET X <- N           // Set X explicitly to N
A = ADD X, N             // Adds mem[N] to X register

g = GRAB X, [N]          // Read X from mem[mem[N]]
o = OFFER X, [N]         // Write X to mem[mem[N]]
r = RECEIVE [N]          // Reads from input stream into mem[N]
b = BRANCH X == 0, [N]     // If X == 0, goto instruction mem[N]
i = INCREASE [N], X        // mem[N] = mem[N] + X
t = TRANSMIT [N]          // Writes to output stream mem[N]
s = SET X <- X XOR [N]      // Performs logic X XOR mem[N], stores in X
a = ADD X, [N]             // Adds mem[mem[N]] to X register

GORBIT-ROM - Program stream is in external memory
GORBIT-RAM - Program stream is in memory, each instruction is 2 bytes,
therefore PC+=2 per op
