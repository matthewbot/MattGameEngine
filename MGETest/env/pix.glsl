uniform sampler2D mge_texture0;
uniform sampler2D mge_texture1;
uniform vec3 extracolor;

void main() {
	if (texture2D(mge_texture0, gl_TexCoord[0].st) == texture2D(mge_texture1, gl_TexCoord[1].st))
		gl_FragColor = vec4(0, 1, 0, 1);
	else
		gl_FragColor = vec4(1, 0, 0, 1);
		
	gl_FragColor += vec4(extracolor, 0);
}

