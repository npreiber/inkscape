#ifndef SEEN_HELPER_FNS_H
#define SEEN_HELPER_FNS_H
/** \file
 *
 * Some helper functions
 *
 * Authors:
 *   Felipe Corrêa da Silva Sanches <felipe.sanches@gmail.com>
 *
 *
 * Copyright (C) 2006 Hugo Rodrigues
 *
 * Released under GNU GPL, read the file 'COPYING' for more information
 */

#include <string.h>
#include <vector>
#include <sstream>

// calling helperfns_read_number(string, false), it's not obvious, what
// that false stands for. helperfns_read_number(string, HELPERFNS_NO_WARNING)
// can be more clear.
#define HELPERFNS_NO_WARNING false

/* convert localized ascii representation to double
 * the function can only be used to convert numbers as given by gui elements that use localized representation
 * @param value ascii representation of the number
 * @return the converted number
 *
 * Setting warning to false disables conversion error warnings from
 * this function. This can be useful in places, where the input type
 * is not known beforehand. For example, see sp_feColorMatrix_set in
 * sp-fecolormatrix.cpp */
inline double helperfns_read_number(gchar const *value, bool warning = true) {
    if (!value) return 0;
    char *end;
    double ret = g_strtod(value, &end);
    if (*end) {
        if (warning) {
            g_warning("helper-fns::helperfns_read_number() Unable to convert \"%s\" to number", value);
        }
        // We could leave this out, too. If strtod can't convert
        // anything, it will return zero.
        ret = 0;
    }
    return ret;
}

inline bool helperfns_read_bool(gchar const *value, bool default_value){
    if (!value) return default_value;
    switch(value[0]){
        case 't':
            if (strncmp(value, "true", 4) == 0) return true;
            break;
        case 'f':
            if (strncmp(value, "false", 5) == 0) return false;
            break;
    }
    return default_value;
}

/* convert localized ascii representation to double
 * the function can only be used to convert numbers as given by gui elements that use localized representation
 * numbers are delimeted by space
 * @param value ascii representation of the number
 * @param size number of elements in string
 * @return the vector of the converted numbers
 */
inline std::vector<gdouble> helperfns_read_vector(const gchar* value, int size){
        std::vector<gdouble> v(size, (gdouble) 0);
        std::istringstream is(value);
        for(int i = 0; i < size; i++){
        	std::string str;
            is >> str;
            char *end;

            double ret = g_strtod(str.c_str(), &end);
            if (*end) {
                g_warning("helper-fns::helperfns_read_vector() Unable to convert \"%s\" to number", str.c_str());
                // We could leave this out, too. If strtod can't convert
                // anything, it will return zero.
                ret = 0;
            }
            v[i] = ret;
        };
        return v;
}

/* convert localized ascii representation to double
 * the function can only be used to convert numbers as given by gui elements that use localized representation
 * numbers are delimeted by space
 * @param value ascii representation of the number
 * @return the vector of the converted numbers
 */
inline std::vector<gdouble> helperfns_read_vector(const gchar* value){
        std::vector<gdouble> v;

        gchar const* beg = value;
        while(isspace(*beg)) beg++;
        while(*beg)
        {
            char *end;
            double ret = g_strtod(beg, &end);
            if (end==beg){
                g_warning("helper-fns::helperfns_read_vector() Unable to convert \"%s\" to number", beg);
                // We could leave this out, too. If strtod can't convert
                // anything, it will return zero.
                ret = 0;
            }
            v.push_back(ret);

            beg = end;
            while(isspace(*beg)) beg++;
        }
        return v;
}

#endif /* !SEEN_HELPER_FNS_H */

/*
  Local Variables:
  mode:c++
  c-file-style:"stroustrup"
  c-file-offsets:((innamespace . 0)(inline-open . 0)(case-label . +))
  indent-tabs-mode:nil
  fill-column:99
  End:
*/
// vim: filetype=cpp:expandtab:shiftwidth=4:tabstop=8:softtabstop=4:encoding=utf-8:textwidth=99 :
