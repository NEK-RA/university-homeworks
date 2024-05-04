# Первое по популярности
import re


def separate_name_val(string):
    name_value_regex = r"(\.begin\s*val\s*(?P<name>.+?)\s*" + \
        r"=\s*{(?P<value>.*?)}\.\s*\.end.)+\s*"
    matches = []
    for line in string:
        match = re.search(name_value_regex, line)
        if match and match.group("name") and match.group("value"):
            matches.append([match.group("name"), match.group("value")])
    return matches


def extract_values(valstr):
    values = []
    single_value_regex = r"q\((?P<value>.*?)\)"
    for val in valstr.split(","):
        match = re.search(single_value_regex, val.strip())
        if match and match.group("value"):
            values.append(match.group("value"))
    return values


def main(istr):
    result = dict()
    istr = istr.replace("\n", " ")\
        .replace("end. .begin", "end.\n.begin")\
        .strip().split("\n")
    matches = separate_name_val(istr)

    for string in matches:
        values = extract_values(string[1])
        result[string[0]] = values
    return result



# testing
print("\n"*10)
test1="""
||.begin val enla ={q(anin_326), q(usin), q(rein_679),q(vebi) }.
.end. .begin val rexe_403= {
q(bisoin_353),q(aesraan_464),q(inin_832)}. .end. ||
"""
test1_expect = {
    'enla': ['anin_326', 'usin', 'rein_679', 'vebi'], 
    'rexe_403': ['bisoin_353', 'aesraan_464', 'inin_832']
}

test2="""
|| .begin val laen_691 = { q(ale_292) , q(inties_358) ,
q(quvebi_976)}. .end. .begin val anla = { q(bima_65) ,
q(gesoxe),q(soteed_123) ,q(edzave_581) }. .end. .begin val esbe =
{q(ain) ,q(isesce_468) }. .end. .begin val leza_378 = { q(teribi)
,q(biatti_207) }. .end. ||
"""
test2_expect = {
    'laen_691': ['ale_292', 'inties_358', 'quvebi_976'],
    'anla': ['bima_65', 'gesoxe', 'soteed_123', 'edzave_581'],
    'esbe': ['ain', 'isesce_468'],
    'leza_378': ['teribi', 'biatti_207']
}

print(main(test1))
print(main(test2))