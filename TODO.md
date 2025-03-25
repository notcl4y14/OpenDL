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
	- [x] Optimize the use of DL_getTypeSize