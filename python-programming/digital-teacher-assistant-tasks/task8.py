def binfixed(num, length=27):
    num = bin(num)[2:]
    if len(num) < length:
        return "0"*(length - len(num)) + num
    return num


# def main(num_str):
#     num = int(num_str)
#     q1_mask = 0b1111111
#     q2_mask = 0b11111 << 7
#     q3_mask = 0b11 << (7+5)
#     q4_mask = 0b1 << (7+5+2)
#     q5_mask = 0b111111 << (7+5+2+1)
#     q6_mask = q5_mask << 6

#     q1 = num & q1_mask
#     q2 = num & q2_mask
#     q3 = num & q3_mask
#     q4 = num & q4_mask
#     q5 = num & q5_mask
#     q6 = num & q6_mask

#     q1bs = binfixed(q1, 7)[:7]
#     q2bs = binfixed(q2, 12)[:5]
#     q3bs = binfixed(q3, 14)[:2]
#     q4bs = binfixed(q4, 15)[:1]
#     q5bs = binfixed(q5, 21)[:6]
#     q6bs = binfixed(q6, 27)[:6]

#     return hex(int(q5bs + q2bs + q6bs + q1bs + q4bs + q3bs, 2))

def main(num_str):
    num = int(num_str)
    bnum = bin(num)[2:]
    p6 = bnum[:6]
    p5 = bnum[6:12]
    p4 = bnum[12]
    p3 = bnum[13:15]
    p2 = bnum[15:20]
    p1 = bnum[20:]
    return hex(int(p5 + p2 + p6 + p1 + p4 + p3, 2))



# testing
print("\n"*10)
print(main('105914617'), '= 0x401cbca')
# print(main('25746216'), '= 0x2363145')
# print(main('133434880'), '= 0x51cfc00')
# print(main('34925427'), '= 0x536439e')