from PIL import Image;

image = Image.open("finch.png");
pixels = image.load();

outfile = open("image.bin", "wb");
for y in range(1):
  for x in range(10):
    #print(pixels[x, y])
    outfile.write(chr(pixels[x, y]))
