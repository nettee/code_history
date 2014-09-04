#!/usr/bin/python3.2

"""meant to replace shell script
    since shell cannot control which file to tar
    conviniently.
    use os.system("COMMAND")
    the file to tar is specified
    in order to reuse
    modify the content in st_list
"""


from os import system as s

st_list = ("ipython",
        "iconfig",
        'imanual',
        'wiki',
        'english',
        'ebook',
        'downloads',
        'bin')

for st in st_list:
    s('tar -cf {0}.tar.gz {0}'.format(st))


