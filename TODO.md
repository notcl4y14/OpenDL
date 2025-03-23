# TODO

- [x] Basic Features
	- [x] Create a struct and methods for Buffer.
	- [x] Create a struct and methods for Attrs for Shader and Path.
	- [x] Create a struct and methods for Shader and Path.
	- [ ] ~~Check if all of them work on different conditions.~~ (already obvious enough that it would work/was lazy to check)
	- [x] Create global variables to store objects.
	- [x] Check if it works on different conditions.
	- [x] Write a few examples to make sure they all work correctly.

- [x] DLSL Features
	- [x] Create a struct and methods for DLSL VM.
	- [x] Add basic OpCodes for DLSL VM.
	- [x] Check if they work.
	- [x] Add Attrs pointer to DLSL VM and OpCodes for it.
	- [x] Add Buffer pointer to DLSL VM and OpCodes for it.

- [x] Implementing DLSL into DL
	- [x] Add global variables for DLSL (Just DLSL VM object)
	- [x] Create a struct and methods for DLCode
	- [x] Add DLCode into DLShader and DLPath
	- [x] Add methods dlApplyShader and dlApplyPath

- [x] TODO comments:
	- [ ] ~~DLSL.c:108; DLSL.c:122. Fix this by creating a util function for copying memory chunks with different sizes~~
		+ This requires casting
	- [x] DL.h:23. Fix this by creating new DLarray variables, like `DLarray_buffers_available`

- [ ] DLSL Redesign:
	- [ ] Make VM support primitive types like char, short, int, float, double instead of just double