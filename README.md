# Информация о том, что это и как сделано
Недоделанное решение задачи полупрозрачного диалога внутри главного окна.
За основу был взят проект курсовой картотека пациентов.
Полупрозрачность задана windowOpacity, движение - переопределением mousePressEvent и mouseMoveEvent.
Создается 2 виджета MainWidget и Widget, создается диалог informationdialog.
MainWidget имеет QStackedLayout, в который инсертится Widget и informationdialog.
Затем задается setStackingMode(QStackedLayout::StackAll), что отображает оба слоя StackedLayout.
Проблема заключается в том, что infromationdialog не ограничен от Widget, и диалог можно переместить за рамки видимой области виджета. ![image](https://github.com/Alk1d/Qt_StackedLayout_transparentDialog/assets/108924851/4d68d5da-cd28-4421-afb5-e7052d3b1578)
Происходит это из-за переопределения mouseMoveEvent'а, предположительно можно совершать проверку позиции в виджете, и при нежелательной позиции отключать движение.
QStackedLayout имеет такую особенность. Если из него удалить виджет, затем заново добавить - он окажется на нижнем слое. Либо Я что-то не так делал :(

