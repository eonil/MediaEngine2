R"(


//#include	"Common.shader"		//	Will be included by C++ compiler.













//	Parameters.
PARAM	mat4	transformP;
PARAM	vec4	instancesP[(EEGLSL_MAX_VERTEX_UNIFORM_VECTOR_COUNT-4)];

/*
 Minus 4 for `transformP` which is 4 * 4D vector.
 One INST is 2 * 4D vectors (32 bytes). 
 Just preserve all possible slots. This is defined as a flat array because
 OpenGL ES 2.0 GLSL 1.00 doesn't support array of structs.
 Also this is a `vec4` array because many OpenGL implementation doesn't
 support individual `float` declaration, and in that case, one float will 
 be expanded to one `vec4` - huge waste of space. For dense packing, this
 must be a 4D vector type which is the only guaranteed type to be aligned 
 as is.
 */






//	Inputs.
IN		float	angleV;
IN		float	indexV;

//	Outputs.
OUT		vec4	colorF;












struct
INST
{
	vec2	position;
	float	inner;
	float	outer;
	vec4	color;
};

INST
instance_at(int index)
{
//	const int	INST_COMPS	=	2+1+1+4;
	/*
	 An instance is 
	 
		8 * floats	=	2 * vector4
	 
	 */
	int	array_index	=	index * 2;
	
	INST	inst;
	inst.position.x	=	instancesP[array_index + 0].x;
	inst.position.y	=	instancesP[array_index + 0].y;
	inst.inner		=	instancesP[array_index + 0].z;
	inst.outer		=	instancesP[array_index + 0].w;
	inst.color.r	=	instancesP[array_index + 1].x;
	inst.color.g	=	instancesP[array_index + 1].y;
	inst.color.b	=	instancesP[array_index + 1].z;
	inst.color.a	=	instancesP[array_index + 1].w;
	return	inst;
}


/*!
 All vertexes must be pre-transformed (would be in CPU) before passing to this shader
 to be drawn batched. This will be updated to perform transform in GPU using SRT 
 information.
 */
void
main()
{
	int		idx1	=	int(indexV);
	INST	inst	=	instance_at(idx1);
	
	float	s1		=	sign(angleV);
	float	r1		=	s1 > 0.0 ? inst.outer : inst.inner;
	
//	float	scl_out	=	s1 * 0.5 + 0.5;
//	float	scl_in	=	s1 * 0.5 - 0.5;
//	float	r1		=	scl_in * inst.inner + scl_out * inst.outer;
	
//	float	r1		=	s1 > 0.0 ? 0.3 : 0.2;
	
	float	t1		=	abs(angleV) - 1.0;
	float	x		=	inst.position.x + (cos(t1) * r1);
	float	y		=	inst.position.y + (sin(t1) * r1);
	
	gl_Position		=	vec4(x, y, 0.0, 1.0) * transformP;		//	Output must be vec4.
	colorF			=	inst.color;
//	colorF			=	vec4(1.0, 1.0, 1.0, 1.0);
}















)" // +END