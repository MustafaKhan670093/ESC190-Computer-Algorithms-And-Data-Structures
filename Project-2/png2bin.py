from PIL import Image

def write_image(image, filename):
    height = image.height
    width = image.width

    f = open(filename, "wb")

    f.write(height.to_bytes(2, byteorder='big'))
    f.write(width.to_bytes(2, byteorder='big'))
    img_raster = []
    for i in range(height):
        for j in range(width):
            img_raster.extend(image.getpixel((j, i)))

    f.write(bytearray(img_raster))
    f.close()

def read_2bytes(f):
    bytes = f.read(2) # [int(f.read(1)), int(f.read(1))]
    return int.from_bytes(bytes, byteorder = 'big')


def read_image(filename):
    f = open(filename, "rb")
    height = read_2bytes(f)
    width = read_2bytes(f)
    image = Image.new("RGB", (width, height))
    bytes = f.read()
    for i in range(height):
        for j in range(width):
            image.putpixel((j, i), (bytes[3*(i*width + j)+0],
                                    bytes[3*(i*width + j)+1],
                                    bytes[3*(i*width + j)+2]))

    return image

# #Write a png image to bin
# image = Image.open("UofTPresidentMericGertler-smaller.jpg")
# write_image(image, "UofTPresidentMericGertler-smaller.bin")
# image = Image.open("da2c206d757d4b461cae0a14927f1ff0.png")
# write_image(image, "charles.bin")

# #Read image from a bin file, save it to png
# im2 = read_image("a.bin")
# im3 = read_image("Level0.5.bin")
# im3.save("Level0.5.png")
# im3 = read_image("Level0.1.bin")
# im3.save("Level0.1.png")
# im3 = read_image("Level2.0.bin")
# im3.save("Level2.0.png")
# im3 = read_image("Level4.0.bin")
# im3.save("Level4.0.png")
# im3 = read_image("Level1.2.bin")
# im3.save("Level1.2.png")


# Write multiple images from bin to png
# for i in range(200):
#     image = read_image("img%d.bin" % i)
#     image.save("img%d.png" % i)

# im3 = read_image("HJoceanSmall1.bin")
# im3.save("HJoceanSmall1.png")
# im3 = read_image("HJoceanSmall.bin")
# im3.save("HJoceanSmall.png")


# Turning images into a GIF
import imageio
images = [read_image(f"img{i}.bin") for i in range(200)]
# for i in range(99):
#     images.append(imageio.imread("img%d.png" % i))
imageio.mimsave('charles.gif', images)


