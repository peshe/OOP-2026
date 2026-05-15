## Задача

### Абстрактен базов клас `CombatUnit`

**Полета:**
- `char* name` - динамично заделен символен низ
- `unsigned int age`
- `int combatLevel`
- `unsigned int salary`

**Чисто виртуални методи:**
- `virtual int getTotalCombatLevel() const = 0`
- `virtual double getTotalMagicPower() const = 0`
- `virtual unsigned int getTotalMonthlyCost() const = 0`
- `virtual const char* getRole() const = 0`
- `virtual void printInfo() const = 0`
- `virtual ~CombatUnit()` - виртуален деструктор, освобождава `name`

> **Важно:** Всеки наследник с динамична памет трябва да имплементира **Rule of Three** - копиращ конструктор, оператор `=`, деструктор.

---

### Клас `Spell`

**Полета:**
- `char* description`
- `SpellType type` - `enum SpellType { FIRE, ICE, LIGHTNING, HEALING, OTHER }`
- `double powerCoefficient` - в `[0.0, 1.0]`

Имплементира Rule of Three за `description`.

---

### Клас `MagicBook`

**Полета:**
- `Spell** pages` - масив от указатели; `nullptr` на дадена позиция = празна страница
- `size_t pageCount_` - текущ брой страници (включително празната в края)
- `size_t capacity` - заделен капацитет

**Методи:**
- `addSpell(const Spell&)` - попълва празната страница, добавя нова `nullptr` в края; при нужда разширява масива (realloc-стратегия)
- `castSpell(size_t pageIndex)` - връща копие на заклинанието, изтрива страницата (size намалява с 1, паметта се преурежда)
- `size_t pageCount() const`
- `size_t spellCount() const` - `pageCount_ - 1`

Имплементира Rule of Three.

---

### Клас `Soldier` - наследява `CombatUnit`

Няма допълнителни динамични полета.

- `getTotalCombatLevel()` → `combatLevel`
- `getTotalMagicPower()` → `0.0`
- `getTotalMonthlyCost()` → `salary`
- `getRole()` → `"Войник"`

---

### Клас `Sergeant` - наследява `CombatUnit`

**Допълнителни полета:**
- `char* platoonDescription`
- `Soldier* soldiers` - динамичен масив от войници (не указатели - обекти)
- `size_t soldierCount`
- `size_t soldierCapacity`

**Методи:**
- `addSoldier(const Soldier&)` - добавя войник, при нужда преразпределя масива
- `getTotalCombatLevel()` → собствено + сума от `soldiers[i].getTotalCombatLevel()`
- `getTotalMagicPower()` → `0.0`
- `getTotalMonthlyCost()` → собствена + сума от `soldiers[i].getTotalMonthlyCost()`
- `getRole()` → `"Сержант"`

Имплементира Rule of Three (дълбоко копиране на `soldiers` и `platoonDescription`).

---

### Клас `Mage` - наследява `CombatUnit`

**Допълнителни полета:**
- `char* battalionDescription`
- `Sergeant* sergeants` - динамичен масив от сержанти (обекти)
- `size_t sergeantCount`
- `size_t sergeantCapacity`
- `double currentMagicPower`
- `MagicBook book`

**Методи:**
- `addSergeant(const Sergeant&)`
- `getTotalCombatLevel()` → собствено + сума от `sergeants[i].getTotalCombatLevel()` *(полиморфно чрез виртуалния метод)*
- `getTotalMagicPower()` → `currentMagicPower`
- `getTotalMonthlyCost()` → собствена + сума от `sergeants[i].getTotalMonthlyCost()`
- `getRole()` → `"Маг"`

Имплементира Rule of Three.

---

### Клас `CommanderInChief` - наследява `CombatUnit`

**Допълнителни полета:**
- `char* armyDescription`
- **Полиморфен контейнер:** `CombatUnit** units` - масив от указатели към `CombatUnit`
- `size_t unitCount`
- `size_t unitCapacity`

**Методи:**
- `addUnit(CombatUnit*)` - добавя указател (не копира обекта!)
- `getTotalCombatLevel()` → собствено + `units[i]->getTotalCombatLevel()` за всеки *(чист полиморфизъм)*
- `getTotalMagicPower()` → сума от `units[i]->getTotalMagicPower()`
- `getTotalMonthlyCost()` → собствена + сума от `units[i]->getTotalMonthlyCost()`
- `getRole()` → `"Главнокомандващ"`
- **Деструктор:** итерира `units`, вика `delete units[i]` за всеки, после `delete[] units`

---

### Бонус - `castFromBook`

```cpp
void castFromBook(size_t unitIndex, size_t pageIndex);
```

- `Mage* mage = dynamic_cast<Mage*>(units[unitIndex])`
- Ако `dynamic_cast` върне `nullptr` → грешка ("Единицата не е маг")
- Взима заклинанието от `mage->book` на `pageIndex`
- Проверява: `mage->currentMagicPower * spell.powerCoefficient <= mage->currentMagicPower` *(винаги вярно - реалната проверка е дали мощта е над минимален праг, напр. `currentMagicPower >= 0.1`)*
- При успех: `mage->book.castSpell(pageIndex)`, редуцира `mage->currentMagicPower *= (1.0 - spell.powerCoefficient)`
- При неуспех: извежда съобщение, не консумира нищо

---

### Програма

```cpp
CommanderInChief* commander = new CommanderInChief(...);

// Добавяне на магове (полиморфно):
Mage* m1 = new Mage(...);
// ... добавяне на сержанти и войници към m1 ...
commander->addUnit(m1);

// Изчисления чрез виртуални методи:
int    totalCombat  = commander->getTotalCombatLevel();
double totalMagic   = commander->getTotalMagicPower();
unsigned int cost   = commander->getTotalMonthlyCost();

delete commander; // верижно изтрива цялата йерархия
```
