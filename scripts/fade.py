import colorsys

if __name__ == '__main__':
    start_color = input('Enter initial color (hex code): ')
    end_color   = input('Enter color to transition to (hex code): ')
    steps       = int(input('Enter number of transition steps: '))

    start_rgb = tuple(int(start_color[i:i+2], 16)/255 for i in (0, 2, 4))
    end_rgb   = tuple(int(end_color[i:i+2], 16)/255 for i in (0, 2, 4))

    start_hsv = colorsys.rgb_to_hsv(*start_rgb)
    end_hsv   = colorsys.rgb_to_hsv(*end_rgb)

    delta_h = end_hsv[0] - start_hsv[0]
    hues = [start_hsv[0] + step * delta_h/(steps - 1) for step in range(steps)]

    color_steps_rgb = [255 * colorsys.hsv_to_rgb(*color) for color in color_steps]

    print(color_steps_rgb)
