R"(


//#include	"Common.shader"		//	Will be included by C++ compiler.

//	Parameters.

//	Inputs.
attribute	vec2	positionCoordinateV;
attribute	vec2	textureCoordinateV;
attribute	vec4	compositionColorV;

//	Outputs.
varying		vec4	compositionColorF;
varying		vec2	textureCoordinateF;




/*!
 All vertexes must be pre-transformed (would be in CPU) before passing to this shader
 to be drawn batched. This will be updated to perform transform in GPU using SRT 
 information.
 */
void
main()
{
	gl_Position			=	vec4(positionCoordinateV.x, positionCoordinateV.y, 0, 1);		//	Output must be vec4.
	compositionColorF	=	compositionColorV;
	textureCoordinateF	=	textureCoordinateV;
	
//	//	Debug...
//	compositionColorF	=	vec4(textureCoordinateV.x,textureCoordinateV.y,0,1);
}







)"