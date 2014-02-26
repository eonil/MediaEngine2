R"(

	//#include	"Common.shader"		//	Will be included by C++ compiler.



	//	Parameters.
	uniform		mat4	localToWorldTransformP;

	//	Inputs.
	attribute	vec4	locationCoordinateV;
	attribute	vec4	compositionColorV;

	//	Outputs.
	varying		vec4	compositionColorF;




	/*!
	 All vertexes must be pre-transformed (would be in CPU) before passing to this shader
	 to be drawn batched. This will be updated to perform transform in GPU using SRT 
	 information.
	 */
	void
	main()
	{
		gl_Position			=	locationCoordinateV * localToWorldTransformP;
		compositionColorF	=	compositionColorV;
	}






)"