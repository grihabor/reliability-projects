================================
Содержательная постановка задачи
================================

Дана система из N модулей. 
У каждого модуля есть M вариантов. 
У каждого варианта 2 характеристики: 

+ надёжность – вещественное значение из интервала ``[0; 1]``

+ стоимость (натуральная величина)

Требуется выбрать для каждого модуля 1 вариант 
так, чтобы надёжность всей системы была максимальной 
при выполнении заданного ограничения на стоимость. 
Считать, что все модули соединены последовательно. 
Параллельно в модуле может быть использован 1 вариант.

Предлогается использовать *метод ветвей и границ*
