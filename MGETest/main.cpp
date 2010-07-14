#include <MGE/kernel/Kernel.h>
#include <MGE/kernel/KernelBuilder.h>
#include <MGE/gfx/system/GraphicsSystemFactory.h>
#include <MGE/res/system/ResourceSystemFactory.h>
#include <MGE/snd/system/AudioSystemFactory.h>
#include <MGE/fs/FileSystemFactory.h>
#include <MGE/util/Logger.h>
#include "TestSystemFactory.h"
#include <iostream>

using namespace mge;
using namespace mgetest;
using namespace std;

int main(int argc, char *argv[]) {
	Logger log;
	log.addStream(cout);
	log.setLogLevel(DEBUG);

	Kernel kernel;
	
	try {
		KernelBuilder builder;
		builder.addFactory(100, new FileSystemFactory("MGETest", "MGETest", argv[0]));
		builder.addFactory(1000, new GraphicsSystemFactory(800, 600, true));
		builder.addFactory(10, new AudioSystemFactory());
		builder.addFactory(10, new ResourceSystemFactory(string("main.res")));
		builder.addFactory(0, new TestSystemFactory());
		
		kernel = builder.buildKernel(log);
  } catch (std::exception &ex) {
  	log.log("main", ERROR) << "Got exception while initializing:" << endl << ex.what() << endl;
  	return 1;
  }
  
	try	{
		kernel.run();
	} catch (std::exception &ex) {
		log.log("main", ERROR) << "Got exception while running: " << endl << ex.what() << endl;
		return 1;
	}
	
	return 0;
}//*/

/*#include <MGE/gfx/util/FloatMat.h>
#include <MGE/gfx/util/FloatVec.h>

int main(int argc, char *argv[]) {
	float mat_f[16] = { 1, 0, 0, 2,
											0, 1, 0, 2,
											0, 0, 1, 2,
											0, 0, 0, 1 };
	float vec_f[4] = { 20, 20, 0, 1 };
	
	FloatMat mat(mat_f);
	FloatVec vec(vec_f);
	
	mat = mat.inverse();
	
	cout << mat << endl;
	
	vec = mat * vec;
	
	cout << vec[0] << " " << vec[1] << " " << vec[2] << " " << vec[3] << endl;
}//*/
