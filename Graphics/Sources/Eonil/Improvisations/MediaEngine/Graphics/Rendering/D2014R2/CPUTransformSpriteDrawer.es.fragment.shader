R"(



//	Parameters.
uniform sampler2D		colorTextureSamplerU;

//	Inputs.
varying highp vec4		compositionColorF;
varying highp vec2		textureCoordinateF;

//	Outputs.




/*!
 
 */
void
main()
{
	gl_FragColor	=	compositionColorF * texture2D(colorTextureSamplerU, textureCoordinateF);
	
//	//	Debugging...
//	gl_FragColor	=	compositionColorF;
}







)"