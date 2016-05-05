# Memory Eater

Uses the [`VirtualAlloc`](https://msdn.microsoft.com/en-us/library/windows/desktop/aa366887%28v=vs.85%29.aspx) 
and [`VirtualLock`](https://msdn.microsoft.com/en-us/library/windows/desktop/aa366895%28v=vs.85%29.aspx) Windows 
functions to efficiently allocate a single large block of memory and lock it in physical memory.

May or may not be useful to create (physical) memory pressure.