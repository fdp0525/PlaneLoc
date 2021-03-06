/*
 * FileGrabber.hpp
 *
 *  Created on: 20 wrz 2016
 *      Author: jachu
 */

#ifndef INCLUDE_FILEGRABBER_HPP_
#define INCLUDE_FILEGRABBER_HPP_

#include <string>
#include <vector>
#include <map>
#include <fstream>

#include <boost/filesystem.hpp>

#include <opencv2/opencv.hpp>

#include <pcl/common/common_headers.h>
#include <pcl/impl/point_types.hpp>

#include "Types.hpp"
#include "Map.hpp"

class FileGrabber{
public:
	class FrameObjInstance{
	public:
		FrameObjInstance(std::string iclassName,
					int iclassId,
					cv::Mat imask)
			:
			className(iclassName),
			classId(iclassId)
		{
			mask = imask.clone();
		}

		std::string getClassName();

		int getClassId();

		cv::Mat getMask();
	private:
		std::string className;

		int classId;

		cv::Mat mask;
	};

	FileGrabber(const cv::FileNode &settings);

	int getFrame(cv::Mat& rgb,
                 cv::Mat& depth,
                 std::vector<FrameObjInstance>& objInstances,
                 std::vector<double>& accelData,
                 Vector7d& pose,
                 Vector7d &vo,
                 bool &voCorr);

	int getFrame(cv::Mat& rgb,
                 cv::Mat& depth,
                 std::vector<FrameObjInstance>& objInstances,
                 std::vector<double>& accelData,
                 Vector7d& pose,
                 Vector7d &vo,
                 bool &voCorr,
			     pcl::PointCloud<pcl::PointXYZRGBNormal>::Ptr pointCloud);
    
    int getFrame(cv::Mat& rgb,
                 cv::Mat& depth,
                 std::vector<FrameObjInstance>& objInstances,
                 std::vector<double>& accelData,
                 Vector7d& pose,
                 Vector7d &vo,
                 bool &voCorr,
                 Map &accMap);
    
    boost::filesystem::path getRgbFilePath(int idx);
private:

	std::vector<boost::filesystem::path> rgbPaths;

	std::vector<boost::filesystem::path> depthPaths;

	std::vector<bool> cloudAvailable;

	std::vector<boost::filesystem::path> cloudPaths;
	
	std::vector<bool> accAvailable;
	
	std::vector<boost::filesystem::path> accPaths;

	std::vector<boost::filesystem::path> instancesPaths;

	std::vector<boost::filesystem::path> labelsPaths;

	std::map<int, std::string> classIdToName;

	std::map<std::string, int> classNameToId;

	std::vector<std::vector<double>> accelDataAll;

	std::vector<Vector7d> groundtruthAll;
	
	std::vector<Vector7d> voAll;
    
    std::vector<bool> voCorrAll;
    
    Vector7d voOffset;

	float depthScale;

	int imageFrame;
	/**
	 *  -1 there is no next frame
	 */
	int nextFrameIdx;
};



#endif /* INCLUDE_FILEGRABBER_HPP_ */
