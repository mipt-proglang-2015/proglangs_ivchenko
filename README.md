# proglangs_ivchenko
Проект по дисциплине **Языки программирования**

*студента 2-го курса магистратуры на каф. АТП ФИВТ МФТИ, гр. 094а Ивченко Олега*

### Условие задачи
> Задача 1.4 со 2-го семестра дисциплины "Алгоритмы и структуры данных" (ШАД).

> Вам дана непустая строка *s*. Нужно найти наибольшее такое *k*, что в строке *s* есть подстрока *t*, являющаяся *k*-повторением. *k*-повторение — это такая строка *t*, что *t = uuu . . . u* (*k* раз подряд выписано *u*), где *u* — некоторая непустая строка.
> В единственной строке входа — строка *s* длиной не более 5 000. Выведите наибольшее
возможное *k*.

Условие дополнено возможностью обрабатывать строки пакетами.

### Установка
* **На Linux:** Запустить `run.sh`.
* **На Windows:** Запустить `run.bat`.

### Запуск
 Запустить скрипт `repeatings.py`, предварительно изучив help к нему.
 
### Тестирование
1. Debug производился с помощью **gdb-pyhon3**.
2. Тестирование на наличие утечек памяти производилось с помощью **Valgring**:

   ```valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all python3 repeatings.py 100```

   Получен результат:
```
==5630== LEAK SUMMARY:
==5630==    definitely lost: 0 bytes in 0 blocks
==5630==    indirectly lost: 0 bytes in 0 blocks
==5630==      possibly lost: 0 bytes in 0 blocks
==5630==    still reachable: 367,502 bytes in 2,540 blocks
==5630==         suppressed: 0 bytes in 0 blocks
```
Утечки типа ```still reachable``` не опасны.

Из [Stackoverflow.com](http://stackoverflow.com/questions/3840582/still-reachable-leak-detected-by-valgrind):
> In general, there is no need to worry about "still reachable" blocks. They don't pose the sort of problem that true memory leaks can cause. For instance, there is normally no potential for heap exhaustion from "still reachable" blocks. This is because these blocks are usually one-time allocations, references to which are kept throughout the duration of the process's lifetime. While you could go through and ensure that your program frees all allocated memory, there is usually no practical benefit from doing so since the operating system will reclaim all of the process's memory after the process terminates, anyway. Contrast this with true memory leaks which, if left unfixed, could cause a process to run out of memory if left running long enough, or will simply cause a process to consume far more memory than is necessary.

> Probably the only time it is useful to ensure that all allocations have matching "frees" is if your leak detection tools cannot tell which blocks are "still reachable" (but Valgrind can do this) or if your operating system doesn't reclaim all of a terminating process's memory (all platforms which Valgrind has been ported to do this).
