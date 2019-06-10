1) Make a dataset of negative images (of same size). To download images from some website (imagenet), please use the "downloadImageFromLink.pu" file.
2) Please use the same code for creating positive images dataset if it do not exist already.
3) Now, we need to create the descriptor file for these negative images. Run the "createBG.py" file.
4) Create two directories: "data" (for cascade information) and "info" (for positive images).
5) Copy the positive image in the workspace (for this example, the image is 50x50).
6) Create the samples using the command below:
"opencv_createsamples -img TestImage.jpg -bg bg.txt -info info/info.lst -pngoutput info -maxxangle 0.5 -maxyangle 0.5 -maxzangle 0.5 -num 1950"

What this does is creates samples, based on the img we specifiy, bg is the background information, info where we will put the info.list output (which is a lot like the bg.txt file), then the -pngoutput is wherever we want to place the newly generated images. 
Finally, we have some optional parameters to make our original image a bit more dynamic and then =num for the number of samples we want to try to create. Great, let's run that. 
Now you should have ~2,000 images in your info directory, and a file called info.lst. This file is your "positives" file basically.
7) Now that we have positive images, we now need to create the vector file, which is basically where we stitch all of our positive images together. 
We will use opencv_createsamples again for this.

"opencv_createsamples -info info/info.lst -num 1950 -w 20 -h 20 -vec positives.vec"

That's our vector file. Here, we just let it know where the info file is, how many images we want to contain in the file, 
what dimensions should the images be in this vector file, and then finally where to output the results. You can make these 
larger if you like, 20 x 20 is probably good enough, and the larger you go, the exponentially longer it will take to run the trainer.
8) Train the classifier:

"opencv_traincascade -data data -vec positives.vec -bg bg.txt -numPos 1800 -numNeg 900 -numStages 10 -w 20 -h 20"

Here, we say where we want the data to go, where the vector file is, where the background file is, how many positive images and negative images to use, 
how many stages, and the width and height. Note that we use significantly less numPos than we have. This is to make room for the stages, which will add to this.
9) "cascade.xml" file is generated in the "data" directory. Use this file to train the classifier.
10) Run the "watchDetect.py" file to test the classifier.