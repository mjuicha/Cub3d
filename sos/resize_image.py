from PIL import Image
import os

# Set the input and output directory paths
input_directory = os.path.expanduser('~/goinfre/g1')  # Path to the folder with the XPM images
output_directory = os.path.expanduser('~/Desktop/g1/resized')  # New folder for resized images

# Create the output directory if it doesn't exist
if not os.path.exists(output_directory):
    os.makedirs(output_directory)

# Resize factor (resizing from 1000px to 100px)
resize_factor = 100 / 1000

# Iterate through the files in the input directory
for filename in os.listdir(input_directory):
    if filename.endswith('.xpm'):
        # Full path to the original image
        input_path = os.path.join(input_directory, filename)
        
        # Full path for saving the resized image
        output_path = os.path.join(output_directory, f"resized_{filename}")
        
        try:
            # Open the image
            with Image.open(input_path) as img:
                # Calculate new size
                new_size = (int(img.width * resize_factor), int(img.height * resize_factor))
                
                # Resize the image
                resized_img = img.resize(new_size)
                
                # Save the resized image
                resized_img.save(output_path)
                print(f"Resized and saved: {output_path}")
        except Exception as e:
            print(f"Error processing {filename}: {e}")
