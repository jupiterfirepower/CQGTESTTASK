На задание потратил 24 часа(3 дня, не стал тратить две недели, 10 дней) и снял свою кандидатуру,
Так как компания CQG не подойдёт в качестве работодателя.
Trading - это по сути гонка за ресурсы, где ресурсы это пары (B, S)
и Вы эту гонку прогирываете (так как Windows Server реально в 5 раз медленнее Linux Server)
Итог - компания CGQ - лузеры(в данном контексте, те кому дастается на семечки, а лучшие позиции проигрывают),
с завышенной самооценкой. :)

Далее, если разместить приложение в Cloud и пересобрать Linux ядро под железо,
то выиграш будет минимальный в 5 раз между сервером Windows и Linux.
Более того еще можно оптимизировать параметры ядра, 
настроить сеть увеличить пропускную способность и т.д. и выиграш будет уже минимум в 5-6 раз.
И где тогда место таким высокоскоростным решениям на С++ под Windows, наверное в мусорнике.

Билл Гейтс после смерти попадёт не в рай и не в ад, а в Корзину.
Интересно, а почему Bill Gates назвал систему "Windows" (окна), а не Gates (двери)?
:)

    Windows - сделано в Америке.
    Linux   - сделано в Европе.
    Make America Great Again

Потратил часик на експерименты, отправляю Вам последний вариант исходных кодов тестого задания.
Вот собственно, результат експеримента исследования.
OS - running in VirtualBox(Windows 10 and Linux Ubuntu 17.10.1)
Windows(Debug)
Time taken by function: 1768 microseconds (1,000 μs	0.001 s) -> 0.0017 секунды
T1+1@50 T7-1@50
T1+2@60 T4-2@60
T1+1@60 T7-1@60

T7-1@60 T2-10@70 T5-3@70 T6-20@80  T1+5@30 T3+1@40 T8+10@90

Input request data:
Windows(Release)
Time taken by function: 54 microseconds -
НО ЭТО НА windows ГДЕ ВСЕ ОТКЛЮЧЕНО телеметрия, задачи связанные с телеметрией и т.д., практически все даже поиск отключен,
в реалии разница будет в 3 минимум раза между Linux Ubuntu и Windows 10
        T1+1@50 T7-1@50
        T1+2@60 T4-2@60
        T1+1@60 T7-1@60

        T7-1@60 T2-10@70 T5-3@70 T6-20@80  T1+5@30 T3+1@40 T8+10@90

        Input request data:
        /Og — включение глобальной оптимизации. 53 microseconds
        При /O2 больше 60 microseconds
        /fp:fast  /Og дали лучший результат в 40-41 микросекунд

g++ -std=c++1z -pipe -Wall -I ~/Documents/VSCODE main.cpp matchengine.hpp -m64 -Ofast -flto -march=native -funroll-loops -o matchengine
clang++-5.0 -std=c++1z -pipe -Wall -I ~/Documents/VSCODE main.cpp -m64 -Ofast -flto -march=native -funroll-loops -o matchengine


Linux
./matchengine
Time taken by function: 21 - 22(g++ compiler) microseconds 
(clang - 24, тут понятно что LVVM наиболее вероятно проиграет)

T1+1@50 T7-1@50
T1+2@60 T4-2@60
T1+1@60 T7-1@60

T7-1@60 T2-10@70 T5-3@70 T6-20@80  T1+5@30 T3+1@40 T8+10@90
Input request data:
54/22 = 2.454545 ~2.5 раза, более того сказать что в Windows параметры оптимизации реально влияют на что-то ...
40/(21-22) ~ 1.8

Linux быстрее, как минимум в 2 раза, но если запустить не в виртуальной машине - то выиграш может быть и больше.
Компания CGQ утверждает - что разрабатывает высокоскоростные решения.
Потенциально Вас будут обыгрывать на рынке аналогичные програмные продукты под Linux, 
также стоит отметить, что разница между серверами Windows и Linux Ubuntu Server  будет еще существенней.

1,000 μs	0.001 s
2,500 μs	0.0025 s
5,000 μs	0.005 s
7,500 μs	0.0075 s
10,000 μs	0.01 s
25,000 μs	0.025 s
50,000 μs	0.05 s
75,000 μs	0.075 s
100,000 μs	0.1 s
250,000 μs	0.25 s
500,000 μs	0.5 s
750,000 μs	0.75 s
1,000,000 μs	1 s
2,500,000 μs	2.5 s
5,000,000 μs	5 s
7,500,000 μs	7.5 s
10,000,000 μs	10 s
25,000,000 μs	25 s
50,000,000 μs	50 s
75,000,000 μs	75 s
100,000,000 μs	100 s
250,000,000 μs	250 s
500,000,000 μs	500 s
750,000,000 μs	750 s
1,000,000,000 μs	1,000 s
2,500,000,000 μs	2,500 s
5,000,000,000 μs	5,000 s
10,000,000,000 μs	10,000 s
