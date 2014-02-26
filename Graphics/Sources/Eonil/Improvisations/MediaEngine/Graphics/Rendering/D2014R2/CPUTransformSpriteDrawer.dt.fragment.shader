R"(



//	Parameters.
uniform sampler2D		colorTextureSamplerU;

//	Inputs.
varying vec4			compositionColorF;
varying vec2			textureCoordinateF;

//	Outputs.




/*!
 
 */
void
main()
{
//	gl_FragColor	=	compositionColorF * texture2D(colorTextureSamplerU, textureCoordinateF);
//	gl_FragColor	=	vec4(1,1,1,1);
	
	//	Debug
	gl_FragColor	=	compositionColorF;
}







)"