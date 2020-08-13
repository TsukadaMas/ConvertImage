void showMainMenu() {
  printf("1. Generate a synthetic test image\n");
  printf("2. Convert an existing color photo to greyscale\n");
  printf("3. Flip an image around the vertical axis\n");
  printf("4. Quit\n");
  printf("Enter your choice: ");
}

void createImage() {
  FILE * outImage = fopen("SampleImage.ppm", "w");
  if (outImage == NULL) {
    printf("could not write");
    return -1;
  }

  int length;
  int width;
  struct pixel pixelColor;

  //get the user inputs of length, width, and color

  printf("enter in the images length ");
  scanf("%d", &length);
  printf("enter in the images width ");
  scanf("%d", &width);
  printf("enter in the images color (red, green, blue) ");
  scanf("%d %d %d", &pixelColor.red, &pixelColor.blue, &pixelColor.green);

  //put the header property values in the file first

  fprintf(outImage, "%s\n", "P3");
  fprintf(outImage, "%d %d\n",width,length);
  fprintf(outImage, "%d\n",255);

  //iterate through the loop and if the row has a mod 2 value of 1 make it all white
  //if the value is 0 then for each value of the width put the color value the user entered

  for(int i=0; i<length; i++){
    if((i % 2) == 0){
        for(int j=0; j<width; j++){
            fprintf(outImage, "%d %d %d\n",pixelColor.red, pixelColor.green, pixelColor.blue);
        }
    }else{
        for(int j=0; j<=width; j++){
            fprintf(outImage, "%d %d %d\n",255, 255, 255);
        }
    }
  }

  //close the newly created image and notify the user

  fclose(outImage);
  printf("SampleImage.ppm is created\n");
}

void greyScale(){

char ogfileName[30];
char p3[3];
int length,width,color_range,luminosityTotal,luminosity,luminosity_avg;
int counter=0;
char newFile[30];
struct pixel color;

//get a file from the user

printf("enter in a ppm file (i.e: somthing.ppm): ");
scanf("%s",ogfileName);

FILE * ogImage = fopen(ogfileName,"r");
char finder = '.';
char * extension = strchr(ogfileName,finder);

/*checking to see if the file exists and also checks
to see if the file the user sent is the right type
 if they arent then print an error statement and go
to the menu*/

  if (ogImage == NULL) {
    printf("File not found\n");
  }else if(strcmp(extension, ".ppm") != 0){
    printf("invalid file format\n");
  }else{
    fscanf(ogImage,"%s",p3);
    fscanf(ogImage,"%d %d",&width,&length);
    fscanf(ogImage,"%d",&color_range);

    /* we want to get the file the user sent
    without the extenstion so we count where the '.' is
    and iterate through the file name the user sent,
    we then save those characters into a new string
    and add the '-greyscale.ppm' to the end of that new
    string and create a file*/

    while (ogfileName[counter] != '.'){
        counter++;
    }
    strncpy(newFile,ogfileName,counter);
    strcat(newFile,"-greyscale.ppm");
 FILE * newImage = fopen(newFile,"w");

 //add the image header properties

 fprintf(newImage,"%s\n",p3);
 fprintf(newImage,"%d %d\n",width,length);
 fprintf(newImage,"%d\n",color_range);

 /*what I'm doing is getting the orignal images pixal values
 saving it into a struct and then mutipling those values by the
luminosity algorithm I then send that value as the rgb values into
 the new file*/

for(int i=0; i<length; i++){
    for(int j=0; j<width; j++){
        for(int k=0; k<=3; k++){
            fscanf(ogImage,"%d",&color.red);
            fscanf(ogImage,"%d",&color.green);
            fscanf(ogImage,"%d",&color.blue);
            luminosity =  (int)((color.red * 0.21) + (color.green * 0.71) + (color.blue * 0.07));
            luminosityTotal += luminosity;
            fprintf(newImage, "%d\n",luminosity);
            fprintf(newImage, "%d\n",luminosity);
            fprintf(newImage, "%d\n",luminosity);
        }
    }
}

//close the file,notify the user a file has been created,
//and display the luminosity average

fclose(newImage);
printf("%s is created\n",newFile);
luminosity_avg = luminosityTotal / (length * width);
printf("the luminosity average is %d\n",luminosity_avg);
}
}

void flip(){

char ogfileName[30];
char p3[3];
int length,width,color_range,placeholder;
int counter=0;
char newFile[30];

//same steps as greyScale() method


printf("enter in a ppm file (i.e: somthing.ppm): ");
scanf("%s",ogfileName);

FILE * ogImage = fopen(ogfileName,"r");
char finder = '.';
char * extension = strchr(ogfileName,finder);
  if (ogImage == NULL) {
    printf("File not found\n");
  }else if(strcmp(extension, ".ppm") != 0){
    printf("invalid file format\n");
  }else{
    fscanf(ogImage,"%s",p3);
    fscanf(ogImage,"%d %d",&width,&length);
    fscanf(ogImage,"%d",&color_range);
    while (ogfileName[counter] != '.'){
        counter++;
    }
    struct pixel rowOfPixels[width];
    strncpy(newFile,ogfileName,counter);
    strcat(newFile,"-flipped.ppm");
 FILE * filpedImage = fopen(newFile,"w");
 fprintf(filpedImage,"%s\n",p3);
 fprintf(filpedImage,"%d %d\n",width,length);
 fprintf(filpedImage,"%d\n",color_range);

 /*what I'm doing here is iterating through the row regularly to get the values
 and store them into an array of structs that is the size of the images width, I
 then iterate through the array of structs starting from the back and send the rgb
 values into the new file
 */

for(int i=0; i<length; i++){
    for(int j=0; j<width; j++){
        for(int k=0; k<=3; k++){
           fscanf(ogImage,"%d",&rowOfPixels[j].red);
           fscanf(ogImage,"%d",&rowOfPixels[j].green);
           fscanf(ogImage,"%d",&rowOfPixels[j].blue);
        }
    }
    for(int j=width; j>0; j--){
        for(int k=0; k<=3; k++){
           fprintf(filpedImage, "%d\n",rowOfPixels[j].red);
           fprintf(filpedImage, "%d\n",rowOfPixels[j].green);
           fprintf(filpedImage, "%d\n",rowOfPixels[j].blue);
        }
    }
}

//once again close the file and notify the user a file has been created

fclose(filpedImage);
printf("%s is created\n",newFile);
}
}
