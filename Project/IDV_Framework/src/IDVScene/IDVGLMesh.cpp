#include <IDVVideo/IDVGLShader.h>
#include <IDVScene/IDVGLMesh.h>
#include <IDVUtils/IDVUtils.h>
#include <IDVParser.h>

void GLMesh::Create() {}
void GLMesh::Create(std::string path_n_Name) {
	//IDVParser parser;
	SigBase = IDVSig::HAS_TEXCOORDS0 | IDVSig::HAS_NORMALS;

	char *vsSourceP = file2string("Shaders/VS_Mesh.glsl");
	char *fsSourceP = file2string("Shaders/FS_Mesh.glsl");

	std::string vstr = std::string(vsSourceP);
	std::string fstr = std::string(fsSourceP);

	free(vsSourceP);
	free(fsSourceP);

	g_pBaseDriver->CreateShader(vstr, fstr, SigBase);

	parser.ReadFile(path_n_Name);
	// vertex read                x      y     z     w      u     v

	for(int i = 0; i < parser.n_meshes + 1; ++i)
	{
		glGenBuffers(1, &parser.v_Meshes[i].VB); //number of meshes?
		//glGenBuffers(1, &parser.v_Meshes[i].VB_mesh[0]);
		glBindBuffer(GL_ARRAY_BUFFER, parser.v_Meshes[i].VB); //number of vertexes
		//				   GL_Stuffs, num_verts * sizeof(vertex struct)                    , start of vertex buffer
		glBufferData(GL_ARRAY_BUFFER, parser.v_Meshes[i].n_Vertexes * sizeof(CVertexMesh_p), &parser.v_Meshes[i].VB_mesh[0], GL_STATIC_DRAW);//
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		for (int j = 0; i < parser.v_Meshes[i].n_mats; ++j) {
			glGenBuffers(1, &parser.v_Meshes[i].Materials[j].IB); //number of material
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, parser.v_Meshes[i].Materials[j].IB);//
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, parser.v_Meshes[i].Materials[j].SubSet_IB.size() * sizeof(unsigned short), &parser.v_Meshes[i].Materials[j].SubSet_IB[0], GL_STATIC_DRAW);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		}
	}
	transform.Identity();
	/*glGenBuffers(1, &Vertexes);
	glBindBuffer(GL_ARRAY_BUFFER, Vertexes);
	glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(CVertexMesh), &VB_model[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);*/

	/*glGenBuffers(1, &Indexes);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Indexes);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned short), &IB_model[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);*/

}

void GLMesh::Transform(float *t) {
	transform = t;
}

void GLMesh::Draw(float *t, float *vp) {

	if (t)
		transform = t;

	unsigned int sig = SigBase;
	sig |= gSig;
	IDVGLShader * s = dynamic_cast<IDVGLShader*>(g_pBaseDriver->GetShaderSig(sig));

	XMATRIX44 VP = vp;
	XMATRIX44 WV = vp;

	glUseProgram(s->ShaderProg);

	glUniformMatrix4fv(s->matWorldUniformLoc, 1, GL_FALSE, &transform.m[0][0]);
	glUniformMatrix4fv(s->matWorldViewProjUniformLoc, 1, GL_FALSE, &transform.m[0][0]);
	glUniformMatrix4fv(s->matWorldViewUniformLoc, 1, GL_FALSE, &WV.m[0][0]);

	for (int i = 0; i < parser.v_Meshes.size(); ++i)
	{
		glBindBuffer(GL_ARRAY_BUFFER, parser.v_Meshes[i].VB);


		glEnableVertexAttribArray(s->vertexAttribLoc);
		glVertexAttribPointer(s->vertexAttribLoc, 4, GL_FLOAT, GL_FALSE, sizeof(CVertexMesh_p), BUFFER_OFFSET(0));
		glEnableVertexAttribArray(s->uvAttribLoc);
		glVertexAttribPointer(s->uvAttribLoc, 2, GL_FLOAT, GL_FALSE, sizeof(CVertexMesh_p), BUFFER_OFFSET(16));
		for (int j = 0; j < parser.v_Meshes[i].n_mats; ++j) {
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, parser.v_Meshes[i].Materials[j].IB);
			glDrawElements(GL_TRIANGLES, parser.v_Meshes[i].Materials[j].SubSet_IB.size(), GL_UNSIGNED_SHORT, 0);
	}
		
	}
	
	/*glBindBuffer(GL_ARRAY_BUFFER, Vertexes);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Indexes);*/

	/*glEnableVertexAttribArray(s->vertexAttribLoc);
	glVertexAttribPointer(s->vertexAttribLoc, 4, GL_FLOAT, GL_FALSE, sizeof(CVertexMesh_p), BUFFER_OFFSET(0));
	glEnableVertexAttribArray(s->uvAttribLoc);
	glVertexAttribPointer(s->uvAttribLoc, 2, GL_FLOAT, GL_FALSE, sizeof(CVertexMesh_p), BUFFER_OFFSET(16));*/

	/*for (int i = 0; i < parser.v_Meshes.size(); ++i) {
		glDrawElements(GL_TRIANGLES, parser.v_Meshes[i].n_Indexes, GL_UNSIGNED_SHORT, 0);
	}*/
	//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);
}

void GLMesh::Destroy() {

}
