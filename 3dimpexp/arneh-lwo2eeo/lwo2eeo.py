#!/usr/bin/env python

import sys, struct, math, operator

VERSION = '1.5.1'
FORMAT_VERSION = 1

flat_shade = False   # if True then no gauraud shading will be applied

# ==============================
# SOME VECTOR FUNCTIONS
# ==============================

def length(v):
    'v is a tuple representing a 3d vector'
    return (v[0]**2 + v[1]**2 + v[2]**2) ** 0.5

def distance(v1, v2):
    return abs(length((v2[0] - v1[0], v2[1] - v1[1], v2[2] - v1[2])))

def add(v1, v2):
    return (v2[0] + v1[0], v2[1] + v1[1], v2[2] + v1[2])

def normalize(v):
    'Normalizes vector v to unit vector'
    len = length(v);
    return (v[0] / len, v[1] / len, v[2] / len)

def cross_prod(u, v):
    'Compute a Vector or Cross Product with another vector'
    assert len(u) == len(v) == 3, 'Cross product only defined for 3D vectors'
    return (u[1]*v[2]-u[2]*v[1],
            u[2]*v[0]-u[0]*v[2],
            u[0]*v[1]-u[1]*v[0])

def dot_prod(u, v):
    'Computes the dot product of two vectors'
    return reduce(operator.add, [(x * y) for (x,y) in zip(u,v)])

class LinearVertices(Exception):
    pass

def get_normal(v1, v2, v3):
    w1 = (v1[0] - v2[0], v1[1] - v2[1], v1[2] - v2[2])
    w2 = (v2[0] - v3[0], v2[1] - v3[1], v2[2] - v3[2])
    normal = cross_prod(w1, w2)
    if normal != (0.0, 0.0, 0.0):
        return normalize(normal)
    else:
        raise LinearVertices


def calculate_normal(vertices):
    'Finds the polygons normal by trying to be somewhat clever in selecting'
    'three points from the polygon to calculate a normal from'

    points_list = [v.coordinate for v in vertices]

    if len(points_list) < 3:
        warnings.warn('polygon with less than 3 points')
        return (0.0, 1.0, 0.0)   # dummy value

    if len(points_list) == 3:
        try:
            return get_normal(*points_list)
        except LinearPolygons:
            pass
    else:
        # find two vertices with furthest distance between them, then
        # average all normals from those to all other points (except
        # for points in line with the first two)
        v1 = points_list[0]
        lengths = [(distance(v1, v2),v2) for v2 in points_list[1:]]
        v2 = max(lengths)[1]

        sum = (0.0, 0.0, 0.0)
        v3_is_last = False
        for v3 in points_list[1:]:
            # don't use v2 twice
            if v3 == v2:
                v3_is_last = True
                continue

            # have to make sure vertices are in the same order as point list
            if v3_is_last:
                vertices = [v1, v2, v3]
            else:
                vertices = [v1, v3, v2]

            try:
                normal = get_normal(*vertices)
            except LinearVertices:
                continue

            sum = add(sum, normal)

        if sum != (0.0, 0.0, 0.0):
            return normalize(sum)

    warnings.warn('polygon with all points in a line. Points: \n%s' % 
                  ', \n'.join([('(%.2f, %.2f, %.2f)' % tuple(point)) for point in points_list]))
    return (0.0, 1.0, 0.0)   # dummy value

def angle_between(u, v):
    'calculates the angle between two unit vectors'
    dp = max(-1.0, min(dot_prod(u,v), 1.0))  # keep between -1.0 and 1.0 to account for rounding errors
    return math.acos(dp)

def deg(x):
    return 180 * x / math.pi

def normal2heading_pitch(normal):
    'Translates a normal vector to a heading/pitch angle offset from X-axis'
    'Assumes the normal is normalized'

    pitch = math.asin(normal[1])

    planar_length = math.sqrt(normal[0] ** 2 + normal[2] ** 2)
    if planar_length == 0:
        heading = 0
    else:
        norm = normal[0] / planar_length
        if normal[2] >= 0:
            heading = math.asin(norm)
        else:
            if norm > 0:
                heading = math.pi - math.asin(norm)
            else:
                heading = -math.pi - math.asin(norm)

    if heading >= math.pi:
        heading -= 2 * math.pi
    if pitch >= math.pi:
        pitch -= 2 * math.pi

    assert(normal[0] - 0.01 < math.cos(pitch) * math.sin(heading) < normal[0] + 0.01)
    assert(normal[1] - 0.01 < math.sin(pitch) < normal[1] + 0.01)
    assert(normal[2] - 0.01 < math.cos(pitch) * math.cos(heading) < normal[2] + 0.01)

    return heading,pitch

def rad2index(rad, is_pitch):
    'EECH uses an index of from 0 (for -PI) to 255 (for PI) for heading values'
    'and 0 (for -PI/2) to 255 (for PI/2) for pitch values'
    if is_pitch:
        scale = 256 / (math.pi)
    else:
        scale = 256 / (2 * math.pi)

    index = bound(rad * scale + 128.0, 0, 255)

    return int(round(index))

def bound(val, min, max):
    if val < min:
        return min
    elif val > max:
        return max
    else:
        return val

def average_polygon_normals(*polygons):
    res = [0,0,0]
    for poly in polygons:
        res[0] += poly.normal[0]
        res[1] += poly.normal[1]
        res[2] += poly.normal[2]
    return normalize(res)

def normal_indices(normal):
    h,p = normal2heading_pitch(normal)
    return rad2index(h, False), rad2index(p, True)

class Warning:
    def __init__(self):
        self.printed_warnings = {}

    def warn(self, *msg):
        msg = ' '.join(msg)
        # only write each warning once
        if msg in self.printed_warnings:
            return

        self.printed_warnings[msg] = None
        sys.stderr.write('Warning: %s\n' % msg)

# ==============================
# === Export EEO Format ===
# ==============================

class TextureList:
    def __init__(self):
        self.textures = {}
    
    def read_texture_enums(self):
        index = 0
        try:
            for texture in file('TEXTURES.TXT'):
                self.textures[texture.strip()] = index
                index += 1
        except IOError,e:
            warnings.warn('Unable to read texture names file: ' + str(e))

    def get_texture_index(self, texture_name):
        "Index for internal texture names.  For new textures we return 0 and the name"
        start = texture_name.rfind('/')
        end = texture_name.rfind('.')
        texture_name = texture_name[start+1:end]
        try:
            return self.textures[texture_name], None
        except KeyError:
            return 0, texture_name

class Constants:
    def __init__(self, **constants):
        self.__dict__.update(constants)
    def __setattr__(self, var, val):
        raise AttributeError('%s is constant value' % var)

FLAGS = Constants(
    POLYGONS = 1 << 0,
    DETAIL = 1 << 1,
    SMOOTHED = 1 << 2,
    TEXTURED = 1 << 3,
    HAS_LUMIOSITY_TEXTURE = 1 << 4,
    ADDITIVE = 1 << 5,
    TRANSLUCENT = 1 << 6,
    LUMINOUS = 1 << 7,
    HAS_SPECULARITY = 1 << 8,
    TEXTURE_ANIMATION = 1 << 9,
    TEXTURE_FILTERED = 1 << 10,
    TEXTURE_MIPMAPPED = 1 << 11,
    TEXTURE_WRAPPED_U = 1 << 12,
    TEXTURE_WRAPPED_V = 1 << 13
    )

class Surface:
    "Represents a surface in EECH"
    def __init__(self, name):
        self.name = name
        self.polygons = []
        
        self.colour = (0.0, 0.0, 0.0)
        self.reflectivity = 0.0
        self.specularity = 0.0
        self.luminosity = 0.0
        self.transparency = 0.0
        self.translucency = 0.0   # translucency let's light through, without being transparent.  Like paper.
        self.smooth = 0   # If it's a smooth (round) surface which should have gauraud shading applied

        self.image = None        # texture used for surface
        self.texture_index = 0
        self.texture_wrap = (1,1)
        self.uv_map = None       # mapping used for texture.
        self.lumi_uv_map = None  # UV map used for luminosity texture
        self.luminosity_texture_index = 0

        self.smoothing_angle = 0  # cutoff-angle for smooting.  If the angle between two polygons is more than this angle it will be a sharp edge, otherwise smooth
        self.surface_points = {}
        self.texture_name = None  # filename (minus extension) of texture
        self.luminosity_texture_name = None  # filename (minus extension) of luminosity texture

        self.next_unsmooth_point_index = 1

    def rgb_colour(self):
        "Converts from 0.0->1.0 to 0->255 based colours"
        r = bound(int(round(self.colour[0] * 255)), 0, 255)
        g = bound(int(round(self.colour[1] * 255)), 0, 255)
        b = bound(int(round(self.colour[2] * 255)), 0, 255)
        return r,g,b

    def set_image(self, image):
        self.image = image
        if self.image:
            idx,name = textures.get_texture_index(self.image)
            if not idx:
                idx = 1
                if model.current_channel == 'LUMI':
                    self.luminosity_texture_name = name
                else:
                    self.texture_name = name
            if model.current_channel == 'LUMI':
                self.luminosity_texture_index = idx
            else:
                self.texture_index = idx

    def pack_colour(self):
        "Returns colour in EEO-file format"
        colour = list(self.rgb_colour())
        colour.reverse()    # EEO wants it in bgr format

        # add transparency as alpha
        alpha = bound(int((1.0 - self.transparency) * 255), 0, 255)
        colour.append(alpha)
        return struct.pack('<4B', *colour)

    def pack_refl_and_spec(self):
        "Returns reflection and specularity in EEO-file format"
        r = bound(int(round(self.reflectivity * 255)), 0, 255)
        s = bound(int(round(self.specularity * 255)), 0, 255)
        return struct.pack('<2B', r,s)

    def pack_flags(self):
        "Returns a bit representation of the surface flags packed in EEO's format"
        flag16 = 0
        flag8 = 0
        
        flag16 |= FLAGS.POLYGONS   # only supports polygones for now...
        if self.luminosity > 0.01:
            flag16 |= FLAGS.LUMINOUS
        if self.translucency > 0.01 or self.transparency > 0.0:
            flag16 |= FLAGS.TRANSLUCENT
        if self.texture_index:
            flag16 |= FLAGS.TEXTURED
            # enable mipmapping and filtering for all textures for now, as I'm not sure
            # how to get that information from the LWO file...
            flag16 |= FLAGS.TEXTURE_MIPMAPPED
            flag16 |= FLAGS.TEXTURE_FILTERED
        if self.texture_wrap[0] in (1,2):
            flag16 |= FLAGS.TEXTURE_WRAPPED_U
        if self.texture_wrap[1] in (1,2):
            flag16 |= FLAGS.TEXTURE_WRAPPED_V
        if not flat_shade and self.smoothing_angle != 0:
            flag16 |= FLAGS.SMOOTHED

        npoints = len(self.surface_points)
        if npoints > 256:
            sys.exit('Error: each surface may contain at most 256 distinct points.  The surface %s contains %d.  You can solve this by cloning the surface and use each clone for no more than 256 points' % (self.name, npoints))
            
        if npoints == 256:
            npoints = 0
        
        return struct.pack('<HBB', flag16, flag8, npoints)

    def get_surface_point_indices(self, coords):
        r"""Returns the index into the surface's point list for each point for the
        provided coordinates (should be both vertex and texture coordinates for each
        point in the polygon"""
        res = []
        for index in coords:
            # non-smooth surfaces cannot share point indices (because colour is
            # calculated on a point basis, so polygons with differen normals will get
            # the same colour), so add a unique value to each key for each non-smooth
            # polygon
            if self.smooth:
                unique_var = 0
            else:
                unique_var = self.next_unsmooth_point_index
                self.next_unsmooth_point_index += 1

            # we use the actual coordinate as key for this hash, and the value is the
            # index.  This way we can easily find coordinates wich are repeated and
            # return the same value
            index = (index[0],index[1],unique_var)

            # if we already have this point then return the index of it, otherwise
            # insert a new one
            if index not in self.surface_points:
                self.surface_points[index] = len(self.surface_points)
               
            res.append(self.surface_points[index])
        return res

    def get_surface_points(self):
        '''Returns all vertice coordinates for all polygons in this surface.  Sorted by point index'''
        items = [(v,k) for (k,v) in self.surface_points.items()]
        items.sort()
        return [i[1][0] for i in items]

    def get_texture_points(self):
        '''Returns all texture coordinates for all polygons in this surface.  Sorted by point index'''
        items = [(v,k) for (k,v) in self.surface_points.items()]
        items.sort()
        return [i[1][1] for i in items]
#end Surface

class VertexMap:
    def __init__(self, name):
        self.name = name
        self.point_map = {}
        self.polygon_override = {}

    def add_poly_override_map(self, poly_idx, point, map):
        if poly_idx is not None:
            point_map = self.polygon_override.setdefault(poly_idx, {})
        else:
            point_map = self.point_map

        point_map[point] = map

    def get_map(self, poly_idx, point):
        if (poly_idx is not None) and (poly_idx in self.polygon_override):
            poly_map = self.polygon_override[poly_idx]
            if point in poly_map:
                return poly_map[point]

        return self.point_map.get(point, (0,0))

#end VertexMap

class Polygon:
    '''Represents a polygon.  Has methods for getting the points in various formats:
    * vertex index - index into vertex array where point is
    * absolute position
    * relative position (as 16-bit value relative to bounding box) - the format used by EECH
    And normals in formats:
    * absolute normal - unit vector in direction of normal
    * heading/pitch - angle offset from X-axis
    * heading/pitch index - format used by EECH, the heading and pitch is mapped into a byte for each (see rad2index for how mapping is done)
    '''
    def __init__(self, model, vertices):
        self.model = model
        self.vertices = vertices
        self.surf = None
        self.surface_points = []

    def absolute_points(self):
        return [v.coordinate for v in self.vertices]

    def relative_points(self):
        return [model.short_points[v] for v in self.indices]

    def vertex_indices(self):
        return self.vertices

    def eeo_surface_point_indices(self):
        return self.surface_indices

    def num_vertices(self):
        return len(self.vertices)

    def calculate_normal(self):
        self.normal = calculate_normal(self.vertices)
        self.normal_index = model.get_normal_index(normal_indices(self.normal))
        return normal2heading_pitch(self.normal)

#    def normal_indices(self):
#        h,p = self.heading_pitch()
#        return rad2index(h, False), rad2index(p, True)

    def __str__(self):
        return 'Poly: ' + str(map(str, self.vertices))

class Vertex:
    "Represents a vertex (point) used in polygons"
    def __init__(self, index, coord):
        self.index = index
        self.coordinate = coord
        self.polygons = []

    def __getitem__(self, index):
        return self.coordinate[index]

    def __str__(self):
        return 'V%d' % self.index

    def __repr__(self):
        return 'Vertex(%d, (%.2f, %.2f, %.2f))' % ((self.index,) + self.coordinate)


class Object:
    "Represents a complete object"
    def __init__(self):
        self.vertices = []
    
    def global_vertex_index(self, local_index):
        return local_index + self.vertex_offset
    
    def write_vertices(self, file):
    	for vert in self.vertices:
            data = struct.pack("3h", *vert)
            file.write(data)

class Model:
    def __init__(self):
        self.tags = []
        self.ptags = []
        
        self.points = []

        self.polygons = []
        self.eeo_polygons = []   # same polygons, but in different order (sorted by surface)
        self.num_point_refs = 0  # points used in polygons

        self.point_normals = {}
        self.num_point_normals = 0

        self.surfaces = []
        self.surface_lookup = {}
        self.surface_users = {}

        self.vertex_maps = {}
        self.images = {}

    def get_normal_index(self, hp):
        if hp in self.point_normals:
            return self.point_normals[hp]
        else:
            index = self.num_point_normals
            self.num_point_normals += 1
            self.point_normals[hp] = index
            return index

    def num_texture_points(self):
        num = 0
        for surf in self.surfaces:
            if surf.uv_map:
                num += len(surf.surface_points)
            if surf.lumi_uv_map:
                num += len(surf.surface_points)
        return num

    ## ==============================
    ## READ LWO FILE
    ## ==============================

    def read_lwo(self, filename):
        lwo_input = file(filename, 'rb').read()
        input_index = 0
        self.done = False
        self.in_first_layer = False

        tag,total_length,format = self.parse_form(lwo_input)
        if tag != 'FORM' or format != 'LWO2':
            raise Exception('Invalid LWO file')
        
        input_index += 12
        while input_index < 8 + total_length and not self.done:
            length = self.parse_chunk(lwo_input, input_index)

            input_index += length

    def parse_chunk(self, string, start):
        tag, length = self.parse_tag(string, start)
        start += 8

        if tag == 'LAYR':
            # todo: check if hidden layer
            if not self.polygons:  #self.in_first_layer:
                self.in_first_layer = True
            else:
                warnings.warn('ignoring all but first layer')
                self.in_first_layer = False
                return 8 + length
        elif tag == 'TAGS':
            self.parse_tags(string, start, length)
        elif tag == 'PNTS':
            if self.in_first_layer:
                self.parse_points(string, start, length)
        elif tag == 'POLS':
            if self.in_first_layer:
                self.parse_polygons(string, start, length)
        elif tag == 'PTAG':
            if self.in_first_layer:
                self.parse_polygon_tag(string, start, length)
        elif tag == 'SURF':
            self.parse_surface(string, start, length)
        elif tag == 'VMAP':
            self.parse_vertex_map(string, start, length, False)
        elif tag == 'VMAD':
            self.parse_vertex_map(string, start, length, True)
        elif tag == 'CLIP':
            self.parse_clip(string, start, length)
        elif tag == 'BBOX':
            pass # ignore, we calculate our own later
        elif tag == 'VMPA':
            pass  # undocumented, ignore for now
        else:
            print tag, length
            

        if length % 2 != 0:  # pad if unaligned
            length += 1

        return 8 + length

    def parse_nul_string(self, input, start, max_length):
        from cStringIO import StringIO
        string = StringIO()

        for i in range(start, start+max_length):
            if input[i] == '\0':
                break
            string.write(input[i])

        res = string.getvalue()
        length = len(res) + 1
        if length % 2 == 1:
            length += 1

        return res,length

    def parse_tag(self, string, ind, subchunk=False):
        if subchunk:
            format = '>4sH'
            end = ind + 6
        else:
            format = '>4sI'
            end = ind + 8
        return struct.unpack(format, string[ind:end])

    def parse_form(self, string):
        return struct.unpack('>4sI4s', string[:12])

    def parse_tags(self, string, start, length):
        end = start + length
        while start < end:
            tag,slen = self.parse_nul_string(string, start, length)
            start += slen
            self.tags.append(tag)

    def parse_points(self, string, start, length):
        npoints = length / 12
        for i in range(npoints):
            index = len(self.points)
            self.points.append(Vertex(index, struct.unpack('>3f', string[start:start+12])))
            start += 12

    def parse_numverts(self, numverts):
        num = struct.unpack('>H', numverts)[0]
        num &= 0x03ff   # mask out flags
        return num

    def parse_vertices(self, string, start, nverts):
        read = 0
        vertices = []

        for vert in range(nverts):
            if string[start] == 0xff:  # four byte index
                vindex = struct.unpack('>I', string[start:start+4])[0]
                vindex &= 0x00ffffff   # mask out four byte flag
                read += 4
                start += 4
            else:   # two byte index
                vindex = struct.unpack('>H', string[start:start+2])[0]
                read += 2
                start += 2
            vertices.append(vindex)
#            vertices.append(self.points[vindex])

        return vertices,read
            

    def parse_polygons(self, string, start, length):
        if string[start:start+4] != 'FACE':
            warnings.warn('only face polygons supported; ignoring ', string[start:start+4])
            return

        end = start + length
        start += 4

        while start < end:
            nverts = self.parse_numverts(string[start:start+2])
            start += 2

            vertices,read_length = self.parse_vertices(string, start, nverts)
            vertices = [self.points[v] for v in vertices]

            poly = Polygon(self, vertices)
            self.polygons.append(poly)
            for v in vertices:
                v.polygons.append(poly)
            self.num_point_refs += len(vertices)
            start += read_length

    def parse_polygon_tag(self, string, start, length):
        type = string[start:start+4]
        if type != 'SURF':
            warnings.warn('only surface tags supported;  ignoring ' + string[start:start+4])
            return

        end = start + length
        start += 4
        
        while start < end:
            poly,read_length = self.parse_vertices(string, start, 1)
            poly = poly[0]
            start += read_length

            tag = struct.unpack('>H', string[start:start+2])[0]
            tag = self.tags[tag]
            start += 2

            if poly != len(self.ptags):  # most likely deleted polygon
                continue

            self.ptags.append((poly, tag))
            polygon_list = self.surface_users.setdefault(tag, [])
            polygon_list.append(poly)

    def parse_surface(self, string, start, length):
        end = start + length

        name,slen = self.parse_nul_string(string, start, length)
        start += slen

        source,slen = self.parse_nul_string(string, start, length)
        start += slen

        surf = Surface(name)
        self.surfaces.append(surf)
        self.surface_lookup[name] = surf

        if name in self.surface_users:
            surf.polygons = [self.polygons[i] for i in self.surface_users[name]]

        while start < end:
             tag, length = self.parse_tag(string, start, True)
             start += 6

             if tag == 'COLR':
                 surf.colour = self.parse_colour(string, start, length)
             elif tag in ('LUMI', 'SPEC', 'TRNL', 'REFL', 'TRAN'):
                 self.parse_shading_property(surf, tag, string, start, length)
             elif tag == 'BLOK':
                 self.parse_blok(surf, string, start, length)
             elif tag == 'SMAN':
                 self.parse_smoothing_angle(surf, string, start, length)
             elif tag in ('SIDE'):
                 pass  # ignore
             elif tag in ('NODS'):
                 pass  # undocumented, ignore for now
             else:
                 warnings.warn('unsupported surface property: ' + tag)

             start += length
             if start % 2 == 1:
                 start += 1
             assert(length > 0)

    def parse_colour(self, string, start, length):
        col = struct.unpack('>3f', string[start:start+12])
        start += 12

        envelope,length_read = self.parse_vertices(string, start, 1)
        # envelope doesn't seem to be used...
        return col

    def parse_shading_property(self, surf, tag, string, start, length):
        intensity = struct.unpack('>f', string[start:start+4])[0]

        if tag == 'LUMI':
            surf.luminosity = intensity
        elif tag == 'SPEC':
            surf.specularity = intensity
        elif tag == 'TRNL':
            surf.translucency = intensity
        elif tag == 'TRAN':
            surf.transparency = intensity
        elif tag == 'REFL':
            surf.reflectivity = intensity
        else:
            assert(False)

    def parse_blok(self, surf, string, start, length):
        end = start + length

        start += self.parse_blok_header(string, start, length)
        start += self.parse_texture_mapping(string, start, length)

        # parse the other attributes of the surface
        while start < end:
            tag, blok_length = self.parse_tag(string, start, True)
            start += 6

            if tag == 'PROJ':
                self.parse_projection(string, start)
            elif tag == 'VMAP':
                uv_map = self.parse_uv_name(string, start, blok_length)
                if self.current_channel == 'LUMI':
                    surf.lumi_uv_map = self.vertex_maps[uv_map]
                else:
                    surf.uv_map = self.vertex_maps[uv_map]
            elif tag == 'IMAG':
                if self.current_channel != 'LUMI':
                    surf.set_image(self.parse_imag(string, start, length))
            elif tag == 'WRAP':
                if self.current_channel != 'LUMI':
                    surf.texture_wrap = self.parse_wrap(string, start)

            start += blok_length

    def parse_smoothing_angle(self, surf, string, start, length):
        surf.smoothing_angle = struct.unpack('>f', string[start:start+4])[0]

    def parse_blok_header(self, string, start, length):
        tag, blok_length = self.parse_tag(string, start, True)
        start += 6
        end = start + blok_length

        ordinal = self.parse_nul_string(string, start, blok_length)[0]

        start += len(ordinal) + 1
        while start < end:
            tag, chunk_length = self.parse_tag(string, start, True)
            start += 6

            if tag == 'CHAN':
                self.current_channel = string[start:start+4]
            elif tag == 'OPAC':
#                print struct.unpack('>Hf', string[start:start+6])
                pass

            start += chunk_length

        return 6 + blok_length

    def parse_texture_mapping(self, string, start, length):
        tag, blok_length = self.parse_tag(string, start, True)
        start += 6
        end = start + blok_length

        while start < end:
            tag, chunk_length = self.parse_tag(string, start, True)
            start += 6
            start += chunk_length

        return 6 + blok_length

    def parse_projection(self, string, start):
        proj = struct.unpack('>H', string[start:start+2])[0]
        if proj != 5:
            warnings.warn('only UV texture projection supported')

    def parse_uv_name(self, string, start, length):
        name = self.parse_nul_string(string, start, length)[0]
        return name

    def parse_imag(self, string, start, length):
        image_index = self.parse_vertices(string, start, 1)[0][0]
        try:
            return self.images[image_index]
        except KeyError:
            return None

    def parse_wrap(self, string, start):
        u,v = struct.unpack('>HH', string[start:start+4])
        return u,v

    def parse_vertex_map(self, string, start, length, discontinuous):
        type = string[start:start+4]
        start += 6    # ignore dimension as it's always 2 for UV maps
        length -= 6

        if type != 'TXUV':
            warnings.warn('only UV maps supported, not ' + type)
            return

        name,slen = self.parse_nul_string(string, start, length)
        start += slen
        length -= slen
        v_map = self.vertex_maps.setdefault(name, VertexMap(name))

        end = start + length
        while start < end:
            try:
                if discontinuous:
                    [vertex,poly],v_len = self.parse_vertices(string, start, 2)
                    poly = self.polygons[poly]
                else:
                    poly = None
                    [vertex],v_len = self.parse_vertices(string, start, 1)

                vertex = self.points[vertex]

                start += v_len

                uv = struct.unpack('>ff', string[start:start+8])

                # invert vertical coordingate as EECH seems to use opposite
                uv = uv[0], 1.0 - uv[1]
                v_map.add_poly_override_map(poly, vertex, uv)
            except IndexError:
                # happens if the vertex map belongs to a ignored layer.
                # just ignore this vertex map
                pass
            start += 8

    def parse_clip(self, string, start, length):
        end = start + length
        
        index = struct.unpack('>I', string[start:start+4])[0]
        start += 4

        while start < end:
            tag, blok_length = self.parse_tag(string, start, True)
            start += 6

            if tag == 'STIL':
                fname = self.parse_nul_string(string, start, blok_length)[0]
                self.images[index] = fname
            elif tag == 'FLAG':
                pass  # ignore - lightwave documentation doesn't mention this subchunk...
            else:
                warnings.warn('Only still textures supported')

            start += blok_length

    def num_surface_point_refs(self):
        nrefs = 0
        for surf in self.surfaces:
            nrefs += len(surf.get_surface_points())
        return nrefs

    def num_surface_point_normals(self):
        if flat_shade:
            return 0
        
        nnormals = 0
        for surf in self.surfaces:
            if surf.smoothing_angle != 0:
                for poly in surf.polygons:
                    nnormals += len(poly.surface_points)
        return nnormals

    ## ==============================
    ## CALCULATE AND WRITE EEO
    ## ==============================

    def write_eeo(self, filename):
        out_file = file(filename, 'wb')

        self.compute_bounding_box_and_scale_points()
        self.compute_surface_point_indices()
        if not flat_shade:
            self.compute_surface_point_normals()

        self.write_header(out_file)
        self.write_points(out_file)

        self.write_polygon_lengths(out_file)
        self.write_point_normals(out_file)
        self.write_polygon_points(out_file)
        self.write_surfaces(out_file)
        self.write_polygon_normals(out_file)

        # texture
        self.write_texture_points(out_file)
        self.write_surface_points(out_file)
        if not flat_shade:
            self.write_surface_normals(out_file)

        self.write_custom_texture_names(out_file)

        out_file.close()

    def compute_bounding_box_and_scale_points(self):
        xx = [p[0] for p in self.points]
        yy = [p[1] for p in self.points]
        zz = [p[2] for p in self.points]
    
        self.bounding_box = min(xx), max(xx), min(yy), max(yy), min(zz), max(zz)

        xmax = max(map(abs, self.bounding_box[0:2])) or 1
        ymax = max(map(abs, self.bounding_box[2:4])) or 1
        zmax = max(map(abs, self.bounding_box[4:])) or 1

        x_scale = 0x7fff / xmax
        y_scale = 0x7fff / ymax
        z_scale = 0x7fff / zmax

        self.short_points = [[0,0,0] for n in range(len(self.points))]
        for i in range(len(self.points)):
            x,y,z = self.points[i]

            self.short_points[i][0] = int(round(x * x_scale))
            self.short_points[i][1] = int(round(y * y_scale))
            self.short_points[i][2] = int(round(z * z_scale))

            assert -0x8000 <= self.short_points[i][0] <= 0x7fff
            assert -0x8000 <= self.short_points[i][1] <= 0x7fff
            assert -0x8000 <= self.short_points[i][2] <= 0x7fff

    def compute_surface_point_indices(self):
        # Calculate point indices for all polygons.
        # They are indexes into the surface points list, so depend on which surface
        # the polygon belongs to
        for surf, surf_pols in self.surface_users.items():
            surf = self.surface_lookup[surf]
            for poly in [self.polygons[i] for i in surf_pols]:
                indices = poly.vertex_indices()
                if surf.uv_map:
                    uv = [surf.uv_map.get_map(poly, pref) for pref in indices]
                else:
                    uv = [(0,0)] * len(indices)
                
                if surf.lumi_uv_map:
                    lumi_uv = [surf.lumi_uv_map.get_map(poly, pref) for pref in indices]
                else:
                    lumi_uv = [(0,0)] * len(indices)

                poly.surf = surf
                poly.surface_indices = surf.get_surface_point_indices(zip(indices, uv, lumi_uv))
                poly.calculate_normal()

        for surf in self.surfaces:
            self.eeo_polygons.extend(surf.polygons)

    def compute_surface_point_normals(self):
        for surf, surf_pols in self.surface_users.items():
            surf = self.surface_lookup[surf]
            limit = surf.smoothing_angle
            if limit == 0:
                continue

            for poly in [self.polygons[i] for i in surf_pols]:
                # find all bordering polygons and see if any of them has a normal
                # no more than the smoothing angle off. if so we want to create
                # gouraud shading (by adding point normals
                for point in poly.vertices:
                    # TODO: optimization, don't have to recalculate the same
                    # point for each polygon which is connected to it. Its
                    # normal will be the same each time, so just calculate it once
                    smooth_neighbours = []
                    for neighbour in point.polygons:
                        if neighbour == poly or neighbour.surf != surf:
                            continue
                        angle = angle_between(poly.normal, neighbour.normal)
                        if angle < limit:
                            smooth_neighbours.append(neighbour)
                    if smooth_neighbours:
                        normal = average_polygon_normals(poly, *smooth_neighbours)
                    else:
                        normal = poly.normal
                    index = self.get_normal_index(normal_indices(normal))
                    poly.surface_points.append(index)

    def write_header(self, eeo):
        if FORMAT_VERSION == 1:
            nlighting_normals = self.num_point_normals
        else:
            nlighting_normals = self.num_lighting_normals()
        
        for num in [FORMAT_VERSION,
                    len(self.points),
                    len(self.polygons),   # faces
                    len(self.polygons),   # polygoned faces. all faces are polygoned
                    len(self.surface_users),   # surfaces
                    self.num_point_normals,  # point normals
                    nlighting_normals,    # number of lighting normals
                    self.num_point_refs,  # point references
                    self.num_texture_points(),  # texture points
                    self.num_surface_point_refs(),   # surface point references
                    self.num_surface_point_normals() # surface point normals
                    ]:
            self.write_uint(eeo, num)

        data = struct.pack('6f', *self.bounding_box)
	# not sure why there are two bounding boxes...
        eeo.write(data)
        eeo.write(data)
        # radius - use maximum extent for now
        data = struct.pack('<f', max(map(abs, self.bounding_box)))
        eeo.write(data)

    def write_uint(self, eeo, num):
        eeo.write(struct.pack('<I', num))

    def write_points(self, eeo):
        for point in self.short_points:
            eeo.write(struct.pack('<3h', *point))

    def write_polygon_lengths(self, eeo):
        npts = 0
        for poly in self.eeo_polygons:
            npts += poly.num_vertices()
            eeo.write(struct.pack('B', poly.num_vertices()))
        print 'Number of polygons:', len(self.polygons)
        print 'Number of points:', npts

    def write_polygon_points(self, eeo):
        i = 0
        for poly in self.eeo_polygons:
            i += 1
            for pref in poly.eeo_surface_point_indices():
                try:
                    eeo.write(struct.pack('B', pref))
                except struct.error:
                    'Error, a surface contains too many points'

    def num_lighting_normals(self):
        num = 0
        for poly in self.eeo_polygons:
            if not poly.surf.smoothing_angle:
                num += 1
        return num

    def write_polygon_normals(self, eeo):
        pad = 0
        for poly in self.eeo_polygons:
            if not poly.surf.smoothing_angle:
                eeo.write(struct.pack('<H', poly.normal_index))
            else:
                pad += 1
        if FORMAT_VERSION == 1:
            for i in range(pad):
                eeo.write(struct.pack('<H', 0))

    def write_point_normals(self, eeo):
        normals = [(index,val) for (val,index) in self.point_normals.items()]
        normals.sort()
        for dummy,val in normals:
            eeo.write(struct.pack('<2B', *val))

    def write_surfaces(self, eeo):
        new_surface_list = []  # we'll remove unused surfaces
        for surf in self.surfaces:
            if len(surf.polygons) == 0:
                continue

            eeo.write(surf.pack_flags())
            eeo.write(struct.pack('3H',
                surf.texture_index, surf.luminosity_texture_index, len(surf.polygons)))
            eeo.write(surf.pack_refl_and_spec())
            eeo.write(surf.pack_colour())

            new_surface_list.append(surf)
        self.surfaces = new_surface_list

    def write_surface_points(self, eeo):
        for surf in self.surfaces:
            for point in surf.get_surface_points():
                eeo.write(struct.pack('<H', point.index))


    def write_texture_points(self, eeo):
        for surf in self.surfaces:
            if not surf.image:
                continue

            if not surf.uv_map and not surf.lumi_uv_map:
                sys.exit(('\nError: Surfaces with textures must have a UV-map describing'
                         " the texture\nmapping.  The surface '%s' does have a texture "
                         "('%s'), \nbut no UV-map.") % (surf.name, surf.texture_name))
                

            for uv in (surf.uv_map, surf.lumi_uv_map):
                if uv:
                    for map in surf.get_texture_points():
                        eeo.write(struct.pack('<ff', *map))
                    
    def write_surface_normals(self, eeo):
        # need a normal for each point: only if smooth surface
        i = 0
        for surf in self.surfaces:
            if not surf.smoothing_angle:
                continue

            for poly in surf.polygons:
                for point in poly.surface_points:
                    i += 1
                    eeo.write(struct.pack('<H', point))

    def write_custom_texture_names(self, eeo):
        textures = {}
        for surf in self.surfaces:
            if surf.texture_name:
                textures[surf.texture_name] = None
                eeo.write(surf.texture_name)
            eeo.write('\0')

            if surf.luminosity_texture_name:
                textures[surf.luminosity_texture_name] = None
                eeo.write(surf.luminostiy_texture_name)
            eeo.write('\0')

        if textures:
            textures = textures.keys()
            textures.sort()
            print '\nYou will need to provide these textures to EECH:'
            for t in textures:
                print t
#end Model


warnings = Warning()
print '%s version %s\n' % (sys.argv[0], VERSION)
textures = TextureList()
textures.read_texture_enums()

args = sys.argv[1:]
if '-f' in args:
    flat_shade = True
    args.pop(0)

infile = args.pop(0)
if not args:
    outfile = infile.lower().replace('.lwo', '.eeo')
else:
    outfile = args.pop(0)

model = Model()
model.read_lwo(infile)
model.write_eeo(outfile)
print '\nWrote %s successfully!' % outfile
