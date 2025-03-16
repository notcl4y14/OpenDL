# TODO

- [ ] Bugs
	+ [ ] Fix dlShaderBindBufferAttrib realloc sometimes (Yes, SOMETIMES) returning NULL
		* (Still unknown whether this is a bug or supposed to do that, since there can't be more Attribute Buffers than Uniform Attributes)

- [ ] DLSL VM stuff
	+ [ ] Make DLSL VM more advanced
	+ [ ] Make DLSL VM support any type (not just int)
	+ [ ] Make DLSL VM store variables like attribs and dl_BufferValue in another way