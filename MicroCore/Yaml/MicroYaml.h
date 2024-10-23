/** 
 * 
 *  __  __ _             ___             
 * |  \/  (_)__ _ _ ___ / __|___ _ _ ___ 
 * | |\/| | / _| '_/ _ \ (__/ _ \ '_/ -_)
 * |_|  |_|_\__|_| \___/\___\___/_| \___|
 *                                      
 * MIT License
 *
 * Copyright (c) 2024 Alves Quentin
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 * 
 **/

#pragma once 

#include "../Utils/MicroLog.h"

#define YAML_CPP_STATIC_DEFINE
#include <yaml-cpp/yaml.h>

namespace YAML {

    template<>
    struct convert<micro_upoint> {
        static Node encode( const micro_upoint& rhs ) {
            Node node;

            node.push_back( rhs.x );
            node.push_back( rhs.y );

            return node;
        }

        static bool decode( const Node& node, micro_upoint& rhs ) {
            if ( !node.IsSequence( ) || node.size( ) != 2 )
                return false;

            rhs.x = node[ 0 ].as<uint32_t>( );
            rhs.y = node[ 1 ].as<uint32_t>( );

            return true;
        }
    };

    template<>
    struct convert<micro_point> {
        static Node encode( const micro_point& rhs ) {
            Node node;

            node.push_back( rhs.x );
            node.push_back( rhs.y );

            return node;
        }

        static bool decode( const Node& node, micro_point& rhs ) {
            if ( !node.IsSequence( ) || node.size( ) != 2 )
                return false;

            rhs.x = node[ 0 ].as<int32_t>( );
            rhs.y = node[ 1 ].as<int32_t>( );

            return true;
        }
    };

    template<>
    struct convert<micro_vec2> {
        static Node encode( const micro_vec2& rhs ) {
            Node node;

            node.push_back( rhs.x );
            node.push_back( rhs.y );

            return node;
        }

        static bool decode( const Node& node, micro_vec2& rhs ) {
            if ( !node.IsSequence( ) || node.size( ) != 2 )
                return false;

            rhs.x = node[ 0 ].as<float>( );
            rhs.y = node[ 1 ].as<float>( );

            return true;
        }
    };

    template<>
    struct convert<micro_vec3> {
        static Node encode( const micro_vec3& rhs ) {
            Node node;

            node.push_back( rhs.x );
            node.push_back( rhs.y );
            node.push_back( rhs.z );

            return node;
        }

        static bool decode( const Node& node, micro_vec3& rhs ) {
            if ( !node.IsSequence( ) || node.size( ) != 3 )
                return false;

            rhs.x = node[ 0 ].as<float>( );
            rhs.y = node[ 1 ].as<float>( );
            rhs.z = node[ 2 ].as<float>( );

            return true;
        }
    };

    template<>
    struct convert<micro_vec4> {
        static Node encode( const micro_vec4& rhs ) {
            Node node;

            node.push_back( rhs.x );
            node.push_back( rhs.y );
            node.push_back( rhs.z );
            node.push_back( rhs.w );

            return node;
        }

        static bool decode( const Node& node, micro_vec3& rhs ) {
            if ( !node.IsSequence( ) || node.size( ) != 4 )
                return false;

            rhs.x = node[ 0 ].as<float>( );
            rhs.y = node[ 1 ].as<float>( );
            rhs.z = node[ 2 ].as<float>( );
            rhs.z = node[ 3 ].as<float>( );

            return true;
        }
    };

};
