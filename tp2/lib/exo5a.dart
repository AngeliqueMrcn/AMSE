import 'package:flutter/material.dart';
import 'dart:math' as math;

//On génère un plateau de tuiles avec GridView

math.Random random = new math.Random();

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
          padding: const EdgeInsets.all(20),
            crossAxisSpacing: 10,
            mainAxisSpacing: 10,
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
