# coding:utf-8

'''
对索引的输入html进行预处理
1. 把所有的 html 整理到一个文件中
2. 粗略的解析, 获取到每个 html 对应的标题, 正文和 jump_url
3. 去除 html 标签
'''

import os
import re
from bs4 import BeautifulSoup

import sys
reload(sys)
sys.setdefaultencoding('utf8')

input_path = '../data/input/'
output_path = '../data/tmp/raw_input'
url_prefix = 'https://www.boost.org/doc/libs/1_53_0/doc/'

##过滤HTML中的标签
#将HTML中标签等信息去掉
#@param htmlstr HTML字符串.
def filter_tags(htmlstr):
    #先过滤CDATA
    re_cdata=re.compile('//<!\[CDATA\[[^>]*//\]\]>',re.I) #匹配CDATA
    re_script=re.compile('<\s*script[^>]*>[^<]*<\s*/\s*script\s*>',re.I)#Script
    re_style=re.compile('<\s*style[^>]*>[^<]*<\s*/\s*style\s*>',re.I)#style
    re_br=re.compile('<br\s*?/?>')#处理换行
    re_h=re.compile('</?\w+[^>]*>')#HTML标签
    re_comment=re.compile('<!--[^>]*-->')#HTML注释
    s=re_cdata.sub('',htmlstr)#去掉CDATA
    s=re_script.sub('',s) #去掉SCRIPT
    s=re_style.sub('',s)#去掉style

    # 此处需要去掉换行, 于是把 <br> 标签替换成空格
    s=re_br.sub(' ',s)

    s=re_h.sub('',s) #去掉HTML 标签
    s=re_comment.sub('',s)#去掉HTML注释

    #去掉多余的空行, 把空行都替换成空格
    blank_line=re.compile('\n+')
    s=blank_line.sub(' ',s)

    s=replaceCharEntity(s)#替换实体
    return s


##替换常用HTML字符实体.
#使用正常的字符替换HTML中特殊的字符实体.
#你可以添加新的实体字符到CHAR_ENTITIES中,处理更多HTML字符实体.
#@param htmlstr HTML字符串.
def replaceCharEntity(htmlstr):
    CHAR_ENTITIES={'nbsp':' ','160':' ',
                   'lt':'<','60':'<',
                   'gt':'>','62':'>',
                   'amp':'&','38':'&',
                   'quot':'"','34':'"',}

    re_charEntity=re.compile(r'&#?(?P<name>\w+);')
    sz=re_charEntity.search(htmlstr)
    while sz:
        entity=sz.group()#entity全称，如&gt;
        key=sz.group('name')#去除&;后entity,如&gt;为gt
        try:
            htmlstr=re_charEntity.sub(CHAR_ENTITIES[key],htmlstr,1)
            sz=re_charEntity.search(htmlstr)
        except KeyError:
            #以空串代替
            htmlstr=re_charEntity.sub('',htmlstr,1)
            sz=re_charEntity.search(htmlstr)
    return htmlstr


def enum_file(input_path):
    '''
    对 input_path 进行枚举, 枚举出其中所有的文件路径
    此时需要过滤掉其他不是 html 后缀的文件
    '''
    file_list = []
    for basedir, dirnames, filenames in os.walk(input_path):
        for f in filenames:
            file_path = basedir + '/' + f
            if os.path.splitext(file_path)[-1] == '.html':
                file_list.append(file_path)
    return file_list


def parse_url(path):
    '''
    获取到当前 html 对应的在线版本的文档的路径
    '''
    # path 形如
    # ../data/input/html/about.html
    # 预期得到的结果
    # https://www.boost.org/doc/libs/1_53_0/doc/html/about.html
    # 刚才准备好了一个 url_prefix 形如
    # https://www.boost.org/doc/libs/1_53_0/doc/
    return url_prefix + path[len(input_path):]


def parse_title(html):
    soup = BeautifulSoup(html, 'html.parser')
    return soup.find('title').string


def parse_content(html):
    '''
    解析html中的正文, 需要去标签
    '''
    return filter_tags(html)


def parse_file(path):
    '''
    解析文件, 得到一个三元组(jump_url, title, content)
    '''
    html = open(path).read()
    return parse_url(path), parse_title(html), parse_content(html)


def write_result(result, output_file):
    # result[0]:
    # https://www.boost.org/doc/libs/1_53_0/doc/html/unordered/comparison.html
    # result[1]:
    # Comparison with Associative Containers
    if result[0] and result[1] and result[2]:
        output_file.write(result[0] + '\3' + result[1]
                          + '\3' + result[2] + '\n')


def Run():
    '''
    预处理动作的入口函数, 包含了预处理过程中的所有核心流程
    '''
    # 1. 遍历输入路径下的所有 html 文件.
    # file_list 预期得到一个列表, 列表中包含了若干个文件路径
    file_list = enum_file(input_path)
    with open(output_path, 'w') as output_file:
        for f in file_list:
            # 2. 针对每个文件, 读取并解析文件内容(解析出其中的三元组, 并去标签)
            # f 是一个文件的路径. parse_file 就需要打开文件并解析
            result = parse_file(f)
            # result 预期得到一个三元组
            # jump_url, title, content
            # 3. 把解析的结果写到 output_path 里面
            write_result(result, output_file)


def Test1():
    '''
    枚举目录的测试
    '''
    file_list = enum_file(input_path)
    print file_list


def Test2():
    '''
    构造 jump_url
    '''
    path = '../data/input/html/unordered/comparison.html'
    print parse_url(path)


def Test3():
    '''
    测试标题是否解析正确
    '''
    path = '../data/input/html/unordered/comparison.html'
    print parse_file(path)[-1]


if __name__ == '__main__':
    Run()
    # Test1()
    # Test2()
    # Test3()
