#!/usr/bin/env python

import Image, sys, os.path

SINGLE_IMAGE = -1
MASK_IMAGE = -2

def write_image(img, num, from_x, width, from_y, height, out):
    data = img.getdata()
    
    if num > 32:
        out('{  // %d = %s\n' % (num, chr(num)))
    else:
        out('{\n')

    out('\t%d,\n\t%d,\n\t%d,\n\t%d,\n' % (width, height, -width / 2 + 1, -height / 2 + 1))
    
    for y in range(from_y, height):
        out('\t')
        for pixel in [data.getpixel((x, y)) for x in range(from_x, from_x + width)]:
            if (num == SINGLE_IMAGE or 32 <  num < 128) and pixel == (0,0,0):
                out("1,")
            elif num == MASK_IMAGE and pixel not in ((0,0,0), (255,255,255)):
                out("1,")
            else:
                out("0,")
        out('\n')

    if num in (SINGLE_IMAGE, MASK_IMAGE):
        out('};\n')
    else:
        out('},\n')

        
if __name__ == '__main__':
    name = sys.argv[1]
    img = Image.open(name, )

    if True:
        name_stem = os.path.basename(name).split('.')[0]
        out_name = '%s.h' % name_stem
        out = file(out_name, 'w')
        
        out.write('\nstatic const char %s[] =\n' % name_stem)
        write_image(img, SINGLE_IMAGE, 0, img.size[0], 0, img.size[1], out.write)

        out.write('\nstatic const char %s_mask[] =\n' % name_stem)
        write_image(img, MASK_IMAGE, 0, img.size[0], 0, img.size[1], out.write)

        out.close()
    else:
        out = sys.stdout.write
        x = 0
        w = 17
        for i in range(0, 128):
            write_image(img, i, x, w, 0, img.size[1], out)
            if i > 32:
                x += w
