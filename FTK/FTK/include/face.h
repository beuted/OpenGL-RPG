#ifndef FACE_H
#define FACE_H

/**
 * \Class Face : classe représentant une face d'un bloc
 */
class Face {
 public:
   /**
   * Constructeurs
   */
  Face(bool _lum);
  
  Face();

  /**
   * Destructeur
   */
  ~Face();

  /**
   * getters
   */
  bool getLum() const {return lum;}

  /**
   * setters
   */
  void setLum(bool _lum) {lum = _lum;}

 private:
  /**
   * Luminosite de la face
   */
  bool lum;

  bool bite;
};

#endif //FACE_H
