#!/usr/bin/env python3

# version: 0.3.1
# 2013-12-8

""" yate: html generator
"""

import re

def escape(line):
    esc_map = {'&' : '&amp;',
            '<' : '&lt;',
            '>' : '&gt;',
        }
    return ''.join(esc_map[c] if c in esc_map else c for c in line)

def para(p):
    p = escape(p)
    def _code_inline(mobj):
        return "<code>{}</code>".format(mobj.group(1))
    def _em(mobj):
        return "<em>{}</em>".format(mobj.group(1))
    def _strong(mobj):
        return "<strong>{}</strong>".format(mobj.group(1))
    p = re.sub(r'``(.*)``', _code_inline, p)
    p = re.sub(r'___(.*)___', _em, p)
    p = re.sub(r'~~(.*)~~', _strong, p)
    return '<p>{}</p>'.format(p)

def header(s, level=3):
    return '<h{0}>{1}</h{0}>'.format(level, escape(s))

def comment(s):
    return '<!-- {} -->'.format(escape(s))

def blockquote(lines):
    return ("<blockquote>" + '\n'.join(lines) + "</blockquote>")

def code(lines):
    return "<pre><code>" + '\n'.join(lines) + "\n</code></pre>"

def ul(ls):
    ss = []
    for item in ls:
        if isinstance(item, list):
            ss.append("<li>{}</li>".format(ul(item)))
        else:
            ss.append("<li>{}</li>".format(item))

    return "<ul>\n" + '\n'.join(ss) + "\n</ul>"


def ol(ls):
    ss = []
    for item in ls:
        if isinstance(item, list):
            ss.append("<li>{}</li>".format(ol(item)))
        else:
            ss.append("<li>{}</li>".format(item))

    return "<ol>\n" + '\n'.join(ss) + "\n</ol>"


if __name__ == '__main__':
    ls = [1, 2, [3, 4, 5], 6,[7,] ,8]
    print(ul(ls))
