В первом ряду кинотеатра `N+2` мест, крайние заняты персоналом, но `N` мест посередине свободно
`К` школьников входят в зал по очереди, каждый садится как можно дальше от занятых мест: находит самый большой свободный участок в ряду и садится посередине него.
Если число свободных мест нечетно, то он садится точно посередине, если четно то выбирает одно из двух мест посередине.

По данным `N` и `K` определить сколько мест осталось свободными с двух сторон от школьника, который занял место последним (`К`-м по счету)

На входе: `1<=K<=N<=10^18`
На выходе - `2` целых числа в порядке неубывания - кол-во мест с двух сторон от последнего

Примеры:
`N=10, K=1 -> 4,5` (сел посередине)
`N=10, K=2 -> 2,2` (второй садится по середине группы из 5 свободных мест, с каждой стороны по 2 свободных места)
`N=10, K=3 -> 1,2` (после 2го школьника остались промежутки из 4,2,2 мест. Третий выбрал промежуток в 4 места и занял одно из мест посередине)
