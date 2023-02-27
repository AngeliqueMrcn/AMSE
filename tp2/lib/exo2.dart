import 'package:flutter/material.dart';

class DisplayImageWidget extends StatelessWidget {
  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      home: Scaffold(
        appBar: AppBar(
          title: Text('tp2'),
        ),
        body: Center(
          child: ImageTransform(),
        ),
      ),
    );
  }
}

class ImageTransform extends StatefulWidget {
  @override
  _ImageTransformState createState() => _ImageTransformState();
}

class _ImageTransformState extends State<ImageTransform> {
  double _scale = 1.0;
  double _rotation = 0.0;
  bool _isMirrored = false;

  @override
  Widget build(BuildContext context) {
    return Column(
      mainAxisAlignment: MainAxisAlignment.center,
      children: [
        Transform(
          alignment: Alignment.center,
          transform: Matrix4.identity()
            ..scale(_scale)
            ..rotateZ(_rotation)
            ..scale(_isMirrored ? -1.0 : 1.0, 1.0),
          child: Image.asset(
            'assets/images/pic2.jpg',
            width: 200.0,
            height: 200.0,
            fit: BoxFit.cover,
          ),
        ),
        SizedBox(height: 20.0),
        Row(
          mainAxisAlignment: MainAxisAlignment.center,
          children: [
            Text('Scale: '),
            Slider(
              value: _scale,
              min: 0.1,
              max: 2.0,
              onChanged: (value) {
                setState(() {
                  _scale = value;
                });
              },
            ),
          ],
        ),
        Row(
          mainAxisAlignment: MainAxisAlignment.center,
          children: [
            Text('Rotation: '),
            Slider(
              value: _rotation,
              min: 0.0,
              max: 2 * 3.14159,
              onChanged: (value) {
                setState(() {
                  _rotation = value;
                });
              },
            ),
          ],
        ),
        Row(
          mainAxisAlignment: MainAxisAlignment.center,
          children: [
            Text('Mirrored: '),
            Checkbox(
              value: _isMirrored,
              onChanged: (value) {
                setState(() {
                  _isMirrored = true;
                });
              },
            ),
          ],
        ),
      ],
    );
  }
}
