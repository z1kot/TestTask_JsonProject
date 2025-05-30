Unreal Engine 5.3.2 project for working with JSON files.

Ссылка на билд: https://drive.google.com/file/d/148B1DXWCl5gX8hMlwAVYT3im2BhJD-rR/view?usp=sharing

MVC architecture

## Model

- **UObjectData** — хранит состояние одного объекта (ID, имя, позиция, цвет, флаг активности) и вызывает делегат `OnStateChanged` при изменении.
- **AObjectManager** — актор, отвечающий за загрузку/сохранение массива `UObjectData` в JSON-файл и создание интерактивных акторов с этими данными.

Модель полностью изолирована от UI и от ввода: она только хранит данные и уведомляет об их изменении.

## View

- **AInteractiveActor** — визуализация объекта в мире: содержит `UStaticMeshComponent`, подписывается на делегат `OnStateChanged` модели и меняет цвет, видимость меша, ассет меша.
- **UMG-виджеты** (`UObjectListWidget` + `UObjectRowWidget`) — список всех объектов и их текущих состояний на экране. Они связываются с моделью через делегаты, обновляют чекбоксы и текст при изменении.

View не содержит логики изменения модели — его задача только отображать актуальные данные.  
Однако в `UObjectRowWidget` чекбокс одновременно выступает и контроллером: нажатие на него скрывает или показывает объект в мире.

## Controller

- **ABasePlayerController** — при старте создаёт `Model` и `View`. Обрабатывает ввод: по нажатию клавиши **E** меняет цвет объекта перед камерой на случайный из заданного набора.
- Также по нажатию **T** переключает фокус на UI, позволяя изменять состояния чекбоксов или завершить сессию для сохранения текущих данных сцены в JSON.

Контроллер отвечает только за создание Model и View и связывает ввод пользователя с изменением модели, но не содержит саму логику изменения и показа данных.

---

## Json

- Файл для инициализации данных читает файл из Content/Data - по дефолту указан `init_data.json`
- Сохраняет обновленные данные в Saved/ - по дефолту указан `objects_state.json`

## Colors
- Для преобразования названия цвета(red, blue, etc.) в FColor и обратно - написал класс, в котором хранится небольшой словарь с названием цвета и соотвестующего ему FColor.
- Доступны `black`, `white`, `red`, `green`, `blue`, `yellow`, `cyan`, `magenta`, `orange`, `purple`, `gray`
  
## Meshes
- Доступны `Box1`, `Sphere1`, `Cone`, `Cylinder`
