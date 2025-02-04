import png

image_arr = []
image_width = 0
image_height = 0

def to_png(data):
	with open("output.png", "wb") as f:
		w = png.Writer(image_width, image_height, greyscale=False, alpha=True)
		w.write(f, image_arr)

def parse(data):
	global image_width
	global image_height

	data = data.replace("\r", "")
	split = data.split("\n")
	width = int(split[0])
	height = int(split[1])
	area = width * height

	split = split[2:]
	del split[len(split) - 1]

	for i in range(0, len(split)):
		split[i] = int(split[i])
	
	# print(split)

	# for i in range(0, int(area / 4)):
	# 	pi = i + 4 * width
	# 	arr = []
		
	# 	for j in range(0, width * 4):
	# 		arr.append(int(split[pi + j]))
		
	# 	image_arr.append(arr)

	for y in range(0, height):
		arr = []
		
		for x in range(0, width):
			i = y * width + x
			pi = i

			if split[pi] == 0:
				arr.append(0)
				arr.append(0)
				arr.append(0)
				arr.append(255)
			elif split[pi] == 1:
				arr.append(255)
				arr.append(255)
				arr.append(255)
				arr.append(255)
		
		image_arr.append(arr)
	
	image_width = width
	image_height = height

with open("output.txt", "r") as f:
	print("Start")
	parse(f.read())
	# print(image_arr)
	to_png(image_arr)
	print("Done")