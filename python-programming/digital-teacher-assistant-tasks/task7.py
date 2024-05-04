# 5 по популярности
# class Node:

#     def __init__(self, index=None, paths=None, value=None):
#         self.index = index
#         self.paths = paths
#         self.value = value

#     def is_num(self):
#         return self.value is not None

#     def solve(self, lst):
#         cn = self
#         while not cn.is_num():
#             path = lst[cn.index]
#             if path in cn.paths.keys():
#                 cn = cn.paths[path]
#             else:
#                 return None
#         if cn.is_num():
#             return cn.value
#         else:
#             return None


# def makeTree():
#     # Level 4
#     x2level4 = Node(index=2, paths=dict(
#         SMALI=Node(value=1),
#         LSL=Node(value=2),
#         APL=Node(value=3)
#     ))

#     # Level 3
#     x4level3 = Node(index=4, paths=dict(
#         TERRA=Node(value=0),
#         ABAP=x2level4,
#         CLEAN=Node(value=4)
#     ))

#     x2level3 = Node(index=2, paths=dict(
#         SMALI=Node(value=5),
#         LSL=Node(value=6),
#         APL=Node(value=7)
#     ))

#     # Level 2
#     x1level2 = Node(index=1, paths=dict(
#         COBOL=x4level3,
#         ABNF=x2level3,
#         LLVM=Node(value=8)
#     ))

#     x2level2 = Node(index=2, paths=dict(
#         SMALI=Node(value=9),
#         LSL=Node(value=10),
#         APL=Node(value=11)
#     ))

#     # Level 1 - root
#     x3level1 = Node(index=3, paths=dict(
#         XSLT=x1level2,
#         FLUX=x2level2
#     ))
#     return x3level1


# def main(lst):
#     root = makeTree()
#     return root.solve(lst)
#######################################################################################
#######################################################################################
def main(x):
    if x[3] == "FLUX":
        if x[2] == "SMALI":
            return 9
        elif x[2] == "LSL":
            return 10
        else:
            return 11
    if x[1] == "LLVM":
        return 8
    if x[1] == "ABNF" and x[2] == "SMALI":
        return 5
    elif x[1] == "ABNF" and x[2] == "LSL":
        return 6
    elif x[1] == "ABNF" and x[2] == "APL":
        return 7
    if x[1] == "COBOL" and x[4] == "TERRA":
        return 0
    elif x[1] == "COBOL" and x[4] == "CLEAN":
        return 4
    if x[1] == "COBOL" and x[4] == "ABAP" and x[2] == "SMALI":
        return 1
    elif x[1] == "COBOL" and x[4] == "ABAP" and x[2] == "LSL":
        return 2
    else:
        return 3
    
    


# testing
print(main([1970, 'ABNF', 'LSL', 'FLUX', 'TERRA']), "= 10")
# print(main([1970, 'LLVM', 'SMALI', 'FLUX', 'ABAP']), "= 9")
# print(main([2020, 'COBOL', 'SMALI', 'XSLT', 'TERRA']), "= 0")
# print(main([1970, 'ABNF', 'LSL', 'XSLT', 'CLEAN']), "= 6")
# print(main([1970, 'COBOL', 'APL', 'XSLT', 'ABAP']), "= 3")
