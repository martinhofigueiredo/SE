from PIL import Image
import os

def get_png_files_in_folder(folder_path="."):
    png_files = [f for f in os.listdir(folder_path) if f.lower().endswith(".png")]
    return [os.path.join(folder_path, png_file) for png_file in png_files]

def create_gif(png_files, output_gif):
    images = []
    for png_file in png_files:
        img = Image.open(png_file)
        images.append(img)

    # Save as GIF
    images[0].save(output_gif, save_all=True, append_images=images[1:], duration=500, loop=0)

if __name__ == "__main__":
    # Get PNG files in the same folder as the script
    script_folder = os.path.dirname(os.path.abspath(__file__))
    png_files = get_png_files_in_folder(script_folder)

    output_gif = "output.gif"

    create_gif(png_files, output_gif)
    print(f"GIF created: {output_gif}")