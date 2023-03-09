import 'package:flutter/material.dart';
// import 'package:Taquin/util.dart';
import 'dart:math';

//On génère un plateau de tuiles a partir d'une image
// On peut régler le nombre de tuiles (carrées)

class Tile {
  String imageURL;
  Alignment alignment;

  Tile({this.imageURL='assets/images/pic2.jpg', this.alignment=Alignment.center});

  Widget croppedImageTile() {
    return FittedBox(
      fit: BoxFit.fill,
      child: ClipRect(
        child: Container(
          child: Align(
            alignment: this.alignment,
            widthFactor: 0.3,
            heightFactor: 0.3,
            child: Image.network(this.imageURL),
          ),
        ),
      ),
    );
  }

  Widget CutImage(double x, double y, double cases) {
    return FittedBox(
      fit: BoxFit.fill,
      child: ClipRect(
        child: Container(
          child: Align(
            alignment: Alignment(x, y),
            widthFactor: cases,
            heightFactor: cases,
            child: Image.network(this.imageURL),
          ),
        ),
      ),
    );
  }
}

class PositionedTiles extends StatefulWidget {
  const PositionedTiles({key});

  @override
  State<PositionedTiles> createState() => SliderState();
}

Tile tile = new Tile(
    imageURL: 'assets/images/pic2.jpg',
    alignment: Alignment(0, 0));

// A quelle taille on commence

class SliderState extends State<PositionedTiles> {
  double _sliderValue = 4;

  @override
  Widget build(BuildContext context) {
    List<Widget> containers = [];

    for (int i = 0; i < _sliderValue; i++) {
      for (int j = 0; j < _sliderValue; j++) {
        double x = -1 + i * (2 / (_sliderValue - 1));
        double y = -1 + j * (2 / (_sliderValue - 1));
        containers.add(Container(
          color: Colors.red,
          child: SizedBox(
              width: 100,
              height: 100,
              child: Container(
                  child: this
                      .createTileWidgetFrom(tile, y, x, (1 / _sliderValue)))),
        ));
      }
    }

    return Scaffold(
      appBar: AppBar(
        title: Text('TestGridView'),
      ),
      body: Column(
        mainAxisAlignment: MainAxisAlignment.center,
        children: <Widget>[
          SizedBox(
            width: 400,
            height: 400,
            child: GridView.count(
                /*primary: false,*/
                padding: const EdgeInsets.all(20),
                crossAxisSpacing: 2,
                mainAxisSpacing: 2,
                crossAxisCount: _sliderValue.toInt(),
                children: containers),
          ),
          Row(children: <Widget>[
            Text("Taille : "),
            Expanded(
              child: Slider(
                value: _sliderValue,
                min: 2,
                max: 10,
                divisions: 8,
                label: _sliderValue.round().toString(),
                onChanged: (double value) {
                  setState(() {
                    _sliderValue = value;
                  });
                },
              ),
            )
          ]),
        ],
      ),
    );
  }

  Widget createTileWidgetFrom(Tile tile, double x, double y, double cases) {
    return InkWell(
      child: tile.CutImage(x, y, cases),
      onTap: () {
        print("Tu as appuyé sur une touche");
      },
    );
  }
}