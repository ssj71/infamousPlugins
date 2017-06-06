#ifndef OCTOLO_H
#define OCTOLO_H

#define OCTOLO_URI "http://ssj71.github.io/infamousPlugins/plugs.html#octolo"
#define STEREOCTOLO_URI "http://ssj71.github.io/infamousPlugins/plugs.html#stereoctolo"

enum octolo_ports
{
    ATOM_IN =0,
    IN,
    OUT,
    ENABLE,
    LENGTH,
    DRYG,
    WET,
    OCTDOWN,
    OCTUP,
    SLOPE,
    SEQUENCE,
    OVERLAP
};
enum stereoctolo_ports
{
    SATOM_IN =0,
    SIN,
    SOUTL,
    SOUTR,
    SENABLE,
    SLENGTH,
    SDRYG,
    SWET,
    SWETP,
    SOCTDOWN,
    SOCTDOWNP,
    SOCTUP,
    SOCTUPP,
    SSLOPE,
    SSEQUENCE,
    SOVERLAP
};

#endif
