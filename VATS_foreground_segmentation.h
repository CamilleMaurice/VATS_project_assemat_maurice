%descriptor's data structure
% TO DO

char VATS_Foreground_Segmentation_Start(tForegroundSegmentationVATS* descriptor);

%@param in descriptor pointer to data structure containign input parameters at startup time and private data. It must be declared and filed in by the calling process
%returns T255/F0 depending on wheteher the module has successfully been initialized or not

void VATS_Foreground_Segmentation_Stop(tForegroundSegmentationVATS*descriptor);
%@param in descriptor idem

char VATS_Foreground_Segmentation(tForeground_segmentationVATS* descriptor,lplImage* input,char shadows,lplimage *mask);
%computes the FG binary mask corresponding to the given image input and the current state of the segmentation module as indicated byt he given descriptor
%@param in decsriptor idem
%@param in input
%@param in shadows
%@param out mask
