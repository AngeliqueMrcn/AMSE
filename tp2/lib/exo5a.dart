import 'package:flutter/material.dart';
import 'dart:math' as math;

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
          crossAxisCount: 4,
          children: List.generate(
            24,
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
