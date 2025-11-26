# СД на ИС – семинар – група 1 – седмица 6

## Задачи за упражнение с двусвързан списък

### Задача 0
Модифицирайте дадения клас [Node](https://github.com/nikolaGeorgiev3000/data-structures-fmi-is-2025/blob/main/seminars/05-singly-linked-list/Node.h) от предходната седмица, така че той да представя възел от двусвързан списък.

---

### Задача 1
Реализирайте функция `void removeConsecutiveDuplicates(Node* lst)`, която премахва всички последователни повторения на елементи от двусвързания списък `lst`. Премахнатите елементи да се унищожават с `delete`.

```
Вход:
1, 1, 2, 2, 1, 1, 2, 2, 2, 2, 1, 2, 1, 2
Изход:
1, 2, 1, 2, 1, 2, 1, 2
```

---

### Задача 2
Да се дефинира функция `mirror`, която добавя към свързан списък неговото огледално копие.

```
Вход:
1<->4<->5
Изход:
1<->4<->5<->5<->4<->1
```

---

### Задача 3
[LeetCode 430: Flatten a Multilevel Doubly Linked List](https://leetcode.com/problems/flatten-a-multilevel-doubly-linked-list/description/)

## Задачи за упражнение с цикличен списък

### Задача 4
Да се реализират [задачи 1 и 2 от предходната седмица](https://github.com/nikolaGeorgiev3000/data-structures-fmi-is-2025/blob/main/seminars/05-singly-linked-list/README.md#%D0%B7%D0%B0%D0%B4%D0%B0%D1%87%D0%B0-1), но за цикличен списък.

---

### Задача 5
Да се реши [LeetCode 1823: Find the Winner of the Circular Game](https://leetcode.com/problems/find-the-winner-of-the-circular-game/description/), като се използва цикличен списък.