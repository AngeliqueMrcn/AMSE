import 'package:flutter/material.dart';
import 'dart:math' as math;

math.Random random = new math.Random();

void main() => runApp(PositionedTiles());

class PositionedTiles extends StatelessWidget {
  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      title: 'Plateau de tuiles',
      home: Scaffold(
        appBar: AppBar(
          title: Text('Plateau de tuiles'),
        ),
        body: GridView.count(
          crossAxisCount: 3,
          crossAxisSpacing : 20,
          mainAxisSpacing : 20,
          children: List.generate(
            9,
            (index) {
              return Container(
                color: Color.fromARGB( 255, random.nextInt(255), random.nextInt(255), random.nextInt(255))
              );
            },
          ),
        ),
      ),
    );
  }
}



/*

import 'package:flutter/material.dart';

void main() => runApp(MyApp());

class MyApp extends StatefulWidget {
  @override
  TuileApp createState() => TuileApp();
}

class TuileApp extends State<MyApp> {
  late int columns;
  late double tileSize;
  final int rows = 6;
  final String imagePath = 'assets/images/0-Star-Wars-memes.jpeg';

  @override
  void initState() {
    super.initState();
    columns = 4;
    tileSize = 0.0;
  }

  void _setColumns(int value) {
    setState(() {
      columns = value;
      tileSize = 0.0;
    });
  }

  void _onLayoutDone(Size size) {
    setState(() {
      tileSize = size.width / columns;
    });
  }

  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      title: 'Plateau de tuiles',
      home: Scaffold(
        appBar: AppBar(
          title: Text('Plateau de tuiles'),
        ),
        body: Column(
          children: [
            SizedBox(
              height: 50.0,
              child: Slider(
                min: 1,
                max: 10,
                value: columns.toDouble(),
                onChanged: (value) => _setColumns(value.toInt()),
              ),
            ),
            Expanded(
              child: LayoutBuilder(
                builder: (context, constraints) {
                  if (tileSize == 0.0) {
                    return SizedBox.shrink();
                  }
                  return GridView.count(
                    crossAxisCount: columns,
                    children: List.generate(
                      columns * rows,
                      (index) {
                        return ClipRect(
                          child: Align(
                            alignment: Alignment.topLeft,
                            child: Image.asset(
                              imagePath,
                              width: tileSize,
                              height: tileSize,
                              alignment: Alignment(
                                -((index % columns) * tileSize) / tileSize,
                                -((index ~/ columns) * tileSize) / tileSize,
                              ),
                            ),
                          ),
                        );
                      },
                    ),
                  );
                },
              ),
            ),
          ],
        ),
      ),
    );
  }
}
*/