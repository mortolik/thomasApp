# Решатель дифференциальных уравнений с разрывными коэффициентами

Этот репозиторий содержит программу для численного решения дифференциальных уравнений с разрывными коэффициентами. Проект реализован на C++ с использованием библиотеки Qt для создания графического интерфейса пользователя (GUI).

## Основные особенности

- **Две задачи**: программа поддерживает решение тестовой и основной задачи.
- **Графический интерфейс**: удобный интерфейс для управления параметрами задачи и визуализации результатов.
- **Графики**: отображение решений и их разности на графиках.
- **Таблицы**: вывод численных результатов в табличном формате.
- **Справка**: автоматическое формирование справки с информацией о результатах решения задачи.

## Структура проекта

- **`MainWindow`**: главное окно программы, содержащее вкладки для тестовой и основной задачи.
- **`SolverWidget`**: виджет для управления вкладками и отображения результатов.
- **`TestTaskWidget`**: виджет для тестовой задачи, включающий графики и таблицу.
- **`MainTaskWidget`**: виджет для основной задачи, включающий графики и таблицу.
- **`SolverModel`**: модель, отвечающая за вычисления и решение задачи.

## Как использовать

1. **Запуск программы**: откройте проект в Qt Creator и запустите его.
2. **Выбор задачи**: переключитесь между вкладками "Test" и "Main" для выбора задачи.
3. **Ввод параметров**: укажите количество узлов в спинбоксе.
4. **Запуск решения**: нажмите кнопку "Run Task" для выполнения задачи.
5. **Просмотр результатов**: результаты отобразятся на графиках и в таблице. Справка с информацией о решении будет обновлена автоматически.

## Зависимости

- **Qt**: библиотека для создания графического интерфейса.
- **C++**: язык программирования, используемый для реализации проекта.
